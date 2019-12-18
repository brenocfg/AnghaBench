#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int n_alternatives; } ;

/* Variables and functions */
 char* ASM_COMMENT_START ; 
 int INSN_CODE (scalar_t__) ; 
 int INSN_UID (scalar_t__) ; 
 int /*<<< orphan*/  asm_out_file ; 
 scalar_t__ debug_insn ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_attr_length (scalar_t__) ; 
 TYPE_1__* insn_data ; 
 int which_alternative ; 

__attribute__((used)) static void
output_asm_name (void)
{
  if (debug_insn)
    {
      int num = INSN_CODE (debug_insn);
      fprintf (asm_out_file, "\t%s %d\t%s",
	       ASM_COMMENT_START, INSN_UID (debug_insn),
	       insn_data[num].name);
      if (insn_data[num].n_alternatives > 1)
	fprintf (asm_out_file, "/%d", which_alternative + 1);
#ifdef HAVE_ATTR_length
      fprintf (asm_out_file, "\t[length = %d]",
	       get_attr_length (debug_insn));
#endif
      /* Clear this so only the first assembler insn
	 of any rtl insn will get the special comment for -dp.  */
      debug_insn = 0;
    }
}