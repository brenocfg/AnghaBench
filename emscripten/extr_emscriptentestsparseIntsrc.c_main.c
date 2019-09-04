#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  test_values ;

/* Variables and functions */
 int /*<<< orphan*/  check_error () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  strtoll (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main() {
  const char* test_values[] = {
    "-9223372036854775809",
    "-9223372036854775808",
    "-9223372036854775807",
    "-2147483649",
    "-2147483648",
    "-2147483647",
    "-5",
    "-1",
    "0",
    "1",
    "5",
    "2147483646",
    "2147483647",
    "2147483648",
    "4294967294",
    "4294967295",
    "4294967296",
    "18446744073709551614",
    "18446744073709551615",
    "18446744073709551616",
  };

  for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
    printf("strtol(\"%s\") = %ld\n", test_values[i], strtol(test_values[i], 0, 0));
    check_error();
    printf("strtoll(\"%s\") = %lld\n", test_values[i], strtoll(test_values[i], 0, 0));
    check_error();
    printf("strtoul(\"%s\") = %lu\n", test_values[i], strtoul(test_values[i], 0, 0));
    check_error();
    printf("strtoull(\"%s\") = %llu\n", test_values[i], strtoull(test_values[i], 0, 0));
    check_error();
    printf("\n");
  }

  printf("strtol(\"0x12\", 0, 0) = %ld\n", strtol("0x12", 0, 0));
  printf("strtol(\"0x12\", 0, 10) = %ld\n", strtol("0x12", 0, 10));
  printf("strtol(\"012\", 0, 0) = %ld\n", strtol("012", 0, 0));
  printf("strtol(\"012\", 0, 10) = %ld\n", strtol("012", 0, 10));
  printf("strtol(\"0y12\", 0, 0) = %ld\n", strtol("0y12", 0, 0));
  printf("strtol(\"hello\", 0, 30) = %ld\n", strtol("hello", 0, 30));
  printf("strtol(\"hello\", 0, 10) = %ld\n", strtol("hello", 0, 10));
  printf("strtol(\"not-a-number\") = %ld\n", strtol("not-a-number", 0, 0));

  char str[] = "  0x12end";
  char* endptr;
  printf("strtol(\"  0x12end\") = %ld\n", strtol(str, &endptr, 0));
  printf("endptr - str = %d\n", endptr - str);
  check_error();

  return 0;
}