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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EQUIV ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ alloc_EXPR_LIST (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__* reg_equiv_alt_mem_list ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
push_reg_equiv_alt_mem (int regno, rtx mem)
{
  rtx it;

  for (it = reg_equiv_alt_mem_list [regno]; it; it = XEXP (it, 1))
    if (rtx_equal_p (XEXP (it, 0), mem))
      return;

  reg_equiv_alt_mem_list [regno]
    = alloc_EXPR_LIST (REG_EQUIV, mem,
		       reg_equiv_alt_mem_list [regno]);
}