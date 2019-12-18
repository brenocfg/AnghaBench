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
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int TYPE_VECTOR (int /*<<< orphan*/ ) ; 
 struct reggroup* all_reggroup ; 
 struct reggroup* float_reggroup ; 
 struct reggroup* general_reggroup ; 
 int /*<<< orphan*/  register_type (struct gdbarch*,int) ; 
 struct reggroup* restore_reggroup ; 
 struct reggroup* save_reggroup ; 
 struct reggroup* vector_reggroup ; 

int
default_register_reggroup_p (struct gdbarch *gdbarch, int regnum,
			     struct reggroup *group)
{
  int vector_p;
  int float_p;
  int raw_p;

  if (REGISTER_NAME (regnum) == NULL
      || *REGISTER_NAME (regnum) == '\0')
    return 0;
  if (group == all_reggroup)
    return 1;
  vector_p = TYPE_VECTOR (register_type (gdbarch, regnum));
  float_p = TYPE_CODE (register_type (gdbarch, regnum)) == TYPE_CODE_FLT;
  /* FIXME: cagney/2003-04-13: Can't yet use gdbarch_num_regs
     (gdbarch), as not all architectures are multi-arch.  */
  raw_p = regnum < NUM_REGS;
  if (group == float_reggroup)
    return float_p;
  if (group == vector_reggroup)
    return vector_p;
  if (group == general_reggroup)
    return (!vector_p && !float_p);
  if (group == save_reggroup || group == restore_reggroup)
    return raw_p;
  return 0;   
}