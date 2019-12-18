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
struct TYPE_2__ {scalar_t__ cond; int uncond_value; int instruction; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAD_COND ; 
 int /*<<< orphan*/  BAD_FPU ; 
 scalar_t__ COND_ALWAYS ; 
 int FAIL ; 
 unsigned int NEON_CHECK_ARCH ; 
 unsigned int NEON_CHECK_CC ; 
 int SUCCESS ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_neon_ext_v1 ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  thumb_mode ; 

__attribute__((used)) static int
vfp_or_neon_is_neon (unsigned check)
{
  /* Conditions are always legal in Thumb mode (IT blocks).  */
  if (!thumb_mode && (check & NEON_CHECK_CC))
    {
      if (inst.cond != COND_ALWAYS)
        {
          first_error (_(BAD_COND));
          return FAIL;
        }
      if (inst.uncond_value != -1)
        inst.instruction |= inst.uncond_value << 28;
    }
  
  if ((check & NEON_CHECK_ARCH)
      && !ARM_CPU_HAS_FEATURE (cpu_variant, fpu_neon_ext_v1))
    {
      first_error (_(BAD_FPU));
      return FAIL;
    }
  
  return SUCCESS;
}