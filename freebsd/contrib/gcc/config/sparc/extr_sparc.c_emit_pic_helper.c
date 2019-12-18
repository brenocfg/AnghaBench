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
 int /*<<< orphan*/  ASM_OUTPUT_ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASM_OUTPUT_LABEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BITS_PER_UNIT ; 
 int FUNCTION_BOUNDARY ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 scalar_t__ flag_delayed_branch ; 
 int floor_log2 (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int pic_helper_emitted_p ; 
 int /*<<< orphan*/  pic_helper_symbol_name ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 
 char** reg_names ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_section ; 

__attribute__((used)) static void
emit_pic_helper (void)
{
  const char *pic_name = reg_names[REGNO (pic_offset_table_rtx)];
  int align;

  switch_to_section (text_section);

  align = floor_log2 (FUNCTION_BOUNDARY / BITS_PER_UNIT);
  if (align > 0)
    ASM_OUTPUT_ALIGN (asm_out_file, align);
  ASM_OUTPUT_LABEL (asm_out_file, pic_helper_symbol_name);
  if (flag_delayed_branch)
    fprintf (asm_out_file, "\tjmp\t%%o7+8\n\t add\t%%o7, %s, %s\n",
	    pic_name, pic_name);
  else
    fprintf (asm_out_file, "\tadd\t%%o7, %s, %s\n\tjmp\t%%o7+8\n\t nop\n",
	    pic_name, pic_name);

  pic_helper_emitted_p = true;
}