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
struct reggroup {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int ALPHA_FP0_REGNUM ; 
 int ALPHA_FPCR_REGNUM ; 
 int ALPHA_UNIQUE_REGNUM ; 
 int ALPHA_ZERO_REGNUM ; 
 char* REGISTER_NAME (int) ; 
 struct reggroup* all_reggroup ; 
 struct reggroup* float_reggroup ; 
 struct reggroup* general_reggroup ; 
 struct reggroup* restore_reggroup ; 
 struct reggroup* save_reggroup ; 
 struct reggroup* system_reggroup ; 

__attribute__((used)) static int
alpha_register_reggroup_p (struct gdbarch *gdbarch, int regnum,
			   struct reggroup *group)
{
  /* Filter out any registers eliminated, but whose regnum is 
     reserved for backward compatibility, e.g. the vfp.  */
  if (REGISTER_NAME (regnum) == NULL || *REGISTER_NAME (regnum) == '\0')
    return 0;

  if (group == all_reggroup)
    return 1;

  /* Zero should not be saved or restored.  Technically it is a general
     register (just as $f31 would be a float if we represented it), but
     there's no point displaying it during "info regs", so leave it out
     of all groups except for "all".  */
  if (regnum == ALPHA_ZERO_REGNUM)
    return 0;

  /* All other registers are saved and restored.  */
  if (group == save_reggroup || group == restore_reggroup)
    return 1;

  /* All other groups are non-overlapping.  */

  /* Since this is really a PALcode memory slot...  */
  if (regnum == ALPHA_UNIQUE_REGNUM)
    return group == system_reggroup;

  /* Force the FPCR to be considered part of the floating point state.  */
  if (regnum == ALPHA_FPCR_REGNUM)
    return group == float_reggroup;

  if (regnum >= ALPHA_FP0_REGNUM && regnum < ALPHA_FP0_REGNUM + 31)
    return group == float_reggroup;
  else
    return group == general_reggroup;
}