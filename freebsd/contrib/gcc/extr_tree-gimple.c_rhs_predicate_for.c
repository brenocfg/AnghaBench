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
typedef  int /*<<< orphan*/  gimple_predicate ;

/* Variables and functions */
 int /*<<< orphan*/  is_gimple_formal_tmp_rhs ; 
 scalar_t__ is_gimple_formal_tmp_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_mem_rhs ; 
 scalar_t__ is_gimple_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_reg_rhs ; 

gimple_predicate
rhs_predicate_for (tree lhs)
{
  if (is_gimple_formal_tmp_var (lhs))
    return is_gimple_formal_tmp_rhs;
  else if (is_gimple_reg (lhs))
    return is_gimple_reg_rhs;
  else
    return is_gimple_mem_rhs;
}