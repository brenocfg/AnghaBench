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

/* Variables and functions */
 int /*<<< orphan*/  assert_err ; 
 int /*<<< orphan*/  assert_err_buff ; 
 int assert_err_num ; 
 int /*<<< orphan*/  num_assert_fails ; 
 int /*<<< orphan*/  num_assert_passes ; 
 int /*<<< orphan*/  num_asserts ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,char const*,char const*,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_passing ; 

void pt_assert_run(
  int result, const char* expr, const char* func, const char* file, int line) {
  
  num_asserts++;
  test_passing = test_passing && result;
  
  if (result) {
    num_assert_passes++;
  } else {
    sprintf(assert_err_buff, 
      "        %i. Assert [ %s ] (%s:%i)\n", 
      assert_err_num+1, expr, file, line );
    strcat(assert_err, assert_err_buff);
    assert_err_num++;
    num_assert_fails++;
  }
  
}