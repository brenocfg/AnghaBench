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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;

/* Variables and functions */
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ asm_noperands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_reload_to_stream (scalar_t__) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_for_asm (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_insn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/ * reg_class_names ; 

__attribute__((used)) static void
spill_failure (rtx insn, enum reg_class class)
{
  if (asm_noperands (PATTERN (insn)) >= 0)
    error_for_asm (insn, "can't find a register in class %qs while "
		   "reloading %<asm%>",
		   reg_class_names[class]);
  else
    {
      error ("unable to find a register to spill in class %qs",
	     reg_class_names[class]);

      if (dump_file)
	{
	  fprintf (dump_file, "\nReloads for insn # %d\n", INSN_UID (insn));
	  debug_reload_to_stream (dump_file);
	}
      fatal_insn ("this is the insn:", insn);
    }
}