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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int ECF_CONST ; 
 int ECF_PURE ; 
 int call_expr_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_call_expr_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
can_value_number_call (tree stmt)
{
  tree call = get_call_expr_in (stmt);

  if (call_expr_flags (call)  & (ECF_PURE | ECF_CONST))
    return true;
  return false;
}