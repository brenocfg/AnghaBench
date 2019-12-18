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
struct ui_file {int dummy; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ MIPS_NUMREGS ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdbarch_register_type (struct gdbarch*,int) ; 
 int /*<<< orphan*/  mips_print_register (struct ui_file*,struct frame_info*,int,int /*<<< orphan*/ ) ; 
 int print_fp_register_row (struct ui_file*,struct frame_info*,int) ; 
 int print_gp_register_row (struct ui_file*,struct frame_info*,int) ; 

__attribute__((used)) static void
mips_print_registers_info (struct gdbarch *gdbarch, struct ui_file *file,
			   struct frame_info *frame, int regnum, int all)
{
  if (regnum != -1)		/* do one specified register */
    {
      gdb_assert (regnum >= NUM_REGS);
      if (*(REGISTER_NAME (regnum)) == '\0')
	error ("Not a valid register for the current processor type");

      mips_print_register (file, frame, regnum, 0);
      fprintf_filtered (file, "\n");
    }
  else
    /* do all (or most) registers */
    {
      regnum = NUM_REGS;
      while (regnum < NUM_REGS + NUM_PSEUDO_REGS)
	{
	  if (TYPE_CODE (gdbarch_register_type (gdbarch, regnum)) ==
	      TYPE_CODE_FLT)
	    {
	      if (all)		/* true for "INFO ALL-REGISTERS" command */
		regnum = print_fp_register_row (file, frame, regnum);
	      else
		regnum += MIPS_NUMREGS;	/* skip floating point regs */
	    }
	  else
	    regnum = print_gp_register_row (file, frame, regnum);
	}
    }
}