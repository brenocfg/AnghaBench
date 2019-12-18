#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
struct TYPE_3__ {int /*<<< orphan*/  (* internal_label ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (scalar_t__) ; 
 int LR_REGNUM ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/  text_section ; 
 int /*<<< orphan*/  thumb_call_reg_needed ; 
 scalar_t__* thumb_call_via_label ; 

__attribute__((used)) static void
arm_file_end (void)
{
  int regno;

  if (! thumb_call_reg_needed)
    return;

  switch_to_section (text_section);
  asm_fprintf (asm_out_file, "\t.code 16\n");
  ASM_OUTPUT_ALIGN (asm_out_file, 1);

  for (regno = 0; regno < LR_REGNUM; regno++)
    {
      rtx label = thumb_call_via_label[regno];

      if (label != 0)
	{
	  targetm.asm_out.internal_label (asm_out_file, "L",
					  CODE_LABEL_NUMBER (label));
	  asm_fprintf (asm_out_file, "\tbx\t%r\n", regno);
	}
    }
}