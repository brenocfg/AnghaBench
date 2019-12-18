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
 int /*<<< orphan*/  INSN_ADDRESSES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 scalar_t__ flag_print_asm_name ; 

void
thumb_final_prescan_insn (rtx insn)
{
  if (flag_print_asm_name)
    asm_fprintf (asm_out_file, "%@ 0x%04x\n",
		 INSN_ADDRESSES (INSN_UID (insn)));
}