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
typedef  enum vfp_reg_pos { ____Placeholder_vfp_reg_pos } vfp_reg_pos ;
struct TYPE_2__ {int instruction; } ;

/* Variables and functions */
 scalar_t__ ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_MERGE_FEATURE_SETS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VFP_REG_Dd 133 
#define  VFP_REG_Dm 132 
#define  VFP_REG_Dn 131 
#define  VFP_REG_Sd 130 
#define  VFP_REG_Sm 129 
#define  VFP_REG_Sn 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  arm_arch_used ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_vfp_ext_v3 ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  thumb_arch_used ; 
 scalar_t__ thumb_mode ; 

__attribute__((used)) static void
encode_arm_vfp_reg (int reg, enum vfp_reg_pos pos)
{
  if ((pos == VFP_REG_Dd || pos == VFP_REG_Dn || pos == VFP_REG_Dm)
      && reg > 15)
    {
      if (ARM_CPU_HAS_FEATURE (cpu_variant, fpu_vfp_ext_v3))
        {
          if (thumb_mode)
            ARM_MERGE_FEATURE_SETS (thumb_arch_used, thumb_arch_used,
                                    fpu_vfp_ext_v3);
          else
            ARM_MERGE_FEATURE_SETS (arm_arch_used, arm_arch_used,
                                    fpu_vfp_ext_v3);
        }
      else
        {
          first_error (_("D register out of range for selected VFP version"));
          return;
        }
    }

  switch (pos)
    {
    case VFP_REG_Sd:
      inst.instruction |= ((reg >> 1) << 12) | ((reg & 1) << 22);
      break;

    case VFP_REG_Sn:
      inst.instruction |= ((reg >> 1) << 16) | ((reg & 1) << 7);
      break;

    case VFP_REG_Sm:
      inst.instruction |= ((reg >> 1) << 0) | ((reg & 1) << 5);
      break;

    case VFP_REG_Dd:
      inst.instruction |= ((reg & 15) << 12) | ((reg >> 4) << 22);
      break;
    
    case VFP_REG_Dn:
      inst.instruction |= ((reg & 15) << 16) | ((reg >> 4) << 7);
      break;
    
    case VFP_REG_Dm:
      inst.instruction |= (reg & 15) | ((reg >> 4) << 5);
      break;

    default:
      abort ();
    }
}