#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void (* func ) () ;int /*<<< orphan*/  suite; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ test_t ;

/* Variables and functions */
 scalar_t__ MAX_NAME ; 
 int MAX_TESTS ; 
 int /*<<< orphan*/  abort () ; 
 int num_tests ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pt_title_case (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 TYPE_1__* tests ; 

void pt_add_test(void (*func)(void), const char* name, const char* suite) {

  test_t test;

  if (num_tests == MAX_TESTS) {
    printf("ERROR: Exceeded maximum test count of %i!\n", 
      MAX_TESTS); abort();
  }
  
  if (strlen(name) >= MAX_NAME) {
    printf("ERROR: Test name '%s' too long (Maximum is %i characters)\n", 
      name, MAX_NAME); abort();
  }
  
  if (strlen(suite) >= MAX_NAME) {
    printf("ERROR: Test suite '%s' too long (Maximum is %i characters)\n", 
      suite, MAX_NAME); abort();
  }
  
  test.func = func;
  pt_title_case(test.name, name);
  pt_title_case(test.suite, suite);
  
  tests[num_tests] = test;
  num_tests++;
}