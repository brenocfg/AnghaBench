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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ REG ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_addr_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legitimate_constant_pool_address_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_in_progress ; 
 int /*<<< orphan*/  replace_equiv_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rs6000_eliminate_indexed_memrefs (rtx operands[2])
{
  if (GET_CODE (operands[0]) == MEM
      && GET_CODE (XEXP (operands[0], 0)) != REG
      && ! legitimate_constant_pool_address_p (XEXP (operands[0], 0))
      && ! reload_in_progress)
    operands[0]
      = replace_equiv_address (operands[0],
			       copy_addr_to_reg (XEXP (operands[0], 0)));

  if (GET_CODE (operands[1]) == MEM
      && GET_CODE (XEXP (operands[1], 0)) != REG
      && ! legitimate_constant_pool_address_p (XEXP (operands[1], 0))
      && ! reload_in_progress)
    operands[1]
      = replace_equiv_address (operands[1],
			       copy_addr_to_reg (XEXP (operands[1], 0)));
}