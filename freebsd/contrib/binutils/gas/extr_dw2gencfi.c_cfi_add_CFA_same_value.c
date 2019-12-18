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
 int /*<<< orphan*/  DW_CFA_same_value ; 
 int /*<<< orphan*/  cfi_add_CFA_insn_reg (int /*<<< orphan*/ ,unsigned int) ; 

void
cfi_add_CFA_same_value (unsigned regno)
{
  cfi_add_CFA_insn_reg (DW_CFA_same_value, regno);
}