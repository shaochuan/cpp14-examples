#include <string>
#include <type_traits>
#include "gtest/gtest.h"

/**
 * Convert light_speed literal to m/s, e.g. 0.8_c means 0.8 * c m/s
 * A demonstration of user defined literal, see `user_defined` TEST
 * below
 */
constexpr long double operator"" _c(long double light_speed) {
  return light_speed * 299'792'458;
}

/**
 * Testing the feature of binary literal.
 * e.g. 0b1001 -> integer 9.
 */
TEST(LITERAL_TEST, binary_literal) {
  // binary literal
  int binary = 0b1001;
  EXPECT_EQ(9, binary);
  // integer is a literal type
  EXPECT_TRUE(std::is_literal_type<decltype(binary)>::value);

  auto binary_seperated = 0b1001'1001;
  EXPECT_EQ(153, binary_seperated);
}

/**
 * Testing the feature of chrono literal.
 */
TEST(LITERAL_TEST, chrono_literal) {
  using namespace std::literals;
  auto t = 1ms;
  bool is_same_type = std::is_same<std::chrono::milliseconds, decltype(t)>::value;
  EXPECT_TRUE(is_same_type);
}

/**
 * Testing the feature of raw string literal
 */
TEST(LITERAL_TEST, raw_literal) {
  auto string_block = R"(
    it is like python's """ raw string inside """
    )";
  EXPECT_EQ(55, strlen(string_block));
}

/**
 * Testing the string literal of std::string.
 */
TEST(LITERAL_TEST, string_literal) {
  using namespace std::literals;
  auto s = "string"s;
  bool is_same_type = std::is_same<std::string, decltype(s)>::value;
  EXPECT_TRUE(is_same_type);
}

/**
 * Testing the feature of user defined literal.
 */
TEST(LITERAL_TEST, user_defined) {
  // user defined literal
  auto ls = 0.8_c;
  long double ans = 0.8 * 299'792'458.0;
  EXPECT_DOUBLE_EQ(ans, ls);
}

/**
 * A demonstration of utf8 string literal.
 */
TEST(LITERAL_TEST, utf8_literal) {
  // utf8 literal
  std::string u8str(u8"☃");
  EXPECT_EQ(u8"\u2603", u8str);
}


