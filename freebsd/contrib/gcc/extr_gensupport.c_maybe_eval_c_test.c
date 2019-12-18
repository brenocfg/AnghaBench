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
struct c_test {char const* expr; int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  condition_table ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct c_test*) ; 

int
maybe_eval_c_test (const char *expr)
{
  const struct c_test *test;
  struct c_test dummy;

  if (expr[0] == 0)
    return 1;

  dummy.expr = expr;
  test = (const struct c_test *)htab_find (condition_table, &dummy);
  if (!test)
    return -1;
  return test->value;
}