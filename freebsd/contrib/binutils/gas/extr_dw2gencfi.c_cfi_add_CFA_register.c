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
 int /*<<< orphan*/  DW_CFA_register ; 
 int /*<<< orphan*/  cfi_add_CFA_insn_reg_reg (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void
cfi_add_CFA_register (unsigned reg1, unsigned reg2)
{
  cfi_add_CFA_insn_reg_reg (DW_CFA_register, reg1, reg2);
}