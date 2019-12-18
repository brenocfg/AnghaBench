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
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ NOTE_INSN_DELETED_LABEL ; 
 scalar_t__ NOTE_LINE_NUMBER (int /*<<< orphan*/ ) ; 
 scalar_t__ NOTE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  output_operand_lossage (char*) ; 

void
output_asm_label (rtx x)
{
  char buf[256];

  if (GET_CODE (x) == LABEL_REF)
    x = XEXP (x, 0);
  if (LABEL_P (x)
      || (NOTE_P (x)
	  && NOTE_LINE_NUMBER (x) == NOTE_INSN_DELETED_LABEL))
    ASM_GENERATE_INTERNAL_LABEL (buf, "L", CODE_LABEL_NUMBER (x));
  else
    output_operand_lossage ("'%%l' operand isn't a label");

  assemble_name (asm_out_file, buf);
}