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
 int default_register_reggroup_p (struct gdbarch*,int,struct reggroup*) ; 
 struct reggroup* float_reggroup ; 
 struct reggroup* general_reggroup ; 
 scalar_t__ i386_fp_regnum_p (int) ; 
 scalar_t__ i386_fpc_regnum_p (int) ; 
 struct reggroup* i386_mmx_reggroup ; 
 int i386_mmx_regnum_p (struct gdbarch*,int) ; 
 scalar_t__ i386_mxcsr_regnum_p (struct gdbarch*,int) ; 
 struct reggroup* i386_sse_reggroup ; 
 scalar_t__ i386_sse_regnum_p (struct gdbarch*,int) ; 
 struct reggroup* vector_reggroup ; 

int
i386_register_reggroup_p (struct gdbarch *gdbarch, int regnum,
			  struct reggroup *group)
{
  int sse_regnum_p = (i386_sse_regnum_p (gdbarch, regnum)
		      || i386_mxcsr_regnum_p (gdbarch, regnum));
  int fp_regnum_p = (i386_fp_regnum_p (regnum)
		     || i386_fpc_regnum_p (regnum));
  int mmx_regnum_p = (i386_mmx_regnum_p (gdbarch, regnum));

  if (group == i386_mmx_reggroup)
    return mmx_regnum_p;
  if (group == i386_sse_reggroup)
    return sse_regnum_p;
  if (group == vector_reggroup)
    return (mmx_regnum_p || sse_regnum_p);
  if (group == float_reggroup)
    return fp_regnum_p;
  if (group == general_reggroup)
    return (!fp_regnum_p && !mmx_regnum_p && !sse_regnum_p);

  return default_register_reggroup_p (gdbarch, regnum, group);
}