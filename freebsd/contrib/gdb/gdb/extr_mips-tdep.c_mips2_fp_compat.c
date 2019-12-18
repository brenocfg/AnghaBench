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
struct TYPE_2__ {int /*<<< orphan*/  fp0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_REGNUM ; 
 int ST0_FR ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int read_register (int /*<<< orphan*/ ) ; 
 int register_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips2_fp_compat (void)
{
  /* MIPS1 and MIPS2 have only 32 bit FPRs, and the FR bit is not
     meaningful.  */
  if (register_size (current_gdbarch, mips_regnum (current_gdbarch)->fp0) ==
      4)
    return 0;

#if 0
  /* FIXME drow 2002-03-10: This is disabled until we can do it consistently,
     in all the places we deal with FP registers.  PR gdb/413.  */
  /* Otherwise check the FR bit in the status register - it controls
     the FP compatiblity mode.  If it is clear we are in compatibility
     mode.  */
  if ((read_register (PS_REGNUM) & ST0_FR) == 0)
    return 1;
#endif

  return 0;
}