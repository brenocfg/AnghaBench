#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf32_arm_link_hash_table {int vfp11_fix; } ;
struct bfd_link_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ i; } ;
typedef  TYPE_1__ obj_attribute ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
#define  BFD_ARM_VFP11_FIX_DEFAULT 129 
#define  BFD_ARM_VFP11_FIX_NONE 128 
 scalar_t__ TAG_CPU_ARCH_V7 ; 
 size_t Tag_CPU_arch ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 TYPE_1__* elf_known_obj_attributes_proc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
bfd_elf32_arm_set_vfp11_fix (bfd *obfd, struct bfd_link_info *link_info)
{
  struct elf32_arm_link_hash_table *globals = elf32_arm_hash_table (link_info);
  obj_attribute *out_attr = elf_known_obj_attributes_proc (obfd);
  
  /* We assume that ARMv7+ does not need the VFP11 denorm erratum fix.  */
  if (out_attr[Tag_CPU_arch].i >= TAG_CPU_ARCH_V7)
    {
      switch (globals->vfp11_fix)
        {
        case BFD_ARM_VFP11_FIX_DEFAULT:
        case BFD_ARM_VFP11_FIX_NONE:
          globals->vfp11_fix = BFD_ARM_VFP11_FIX_NONE;
          break;
        
        default:
          /* Give a warning, but do as the user requests anyway.  */
          (*_bfd_error_handler) (_("%B: warning: selected VFP11 erratum "
            "workaround is not necessary for target architecture"), obfd);
        }
    }
  else if (globals->vfp11_fix == BFD_ARM_VFP11_FIX_DEFAULT)
    /* For earlier architectures, we might need the workaround, but do not
       enable it by default.  If users is running with broken hardware, they
       must enable the erratum fix explicitly.  */
    globals->vfp11_fix = BFD_ARM_VFP11_FIX_NONE;
}