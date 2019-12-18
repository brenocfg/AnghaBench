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
typedef  int /*<<< orphan*/  reloc_howto_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
#define  R_MIPS_COPY 129 
#define  R_MIPS_JUMP_SLOT 128 
 int /*<<< orphan*/ * mips_elf32_rtype_to_howto (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_vxworks_copy_howto_rela ; 
 int /*<<< orphan*/  mips_vxworks_jump_slot_howto_rela ; 

__attribute__((used)) static reloc_howto_type *
mips_vxworks_rtype_to_howto (unsigned int r_type, bfd_boolean rela_p)
{
  switch (r_type)
    {
    case R_MIPS_COPY:
      return &mips_vxworks_copy_howto_rela;
    case R_MIPS_JUMP_SLOT:
      return &mips_vxworks_jump_slot_howto_rela;
    default:
      return mips_elf32_rtype_to_howto (r_type, rela_p);
    }
}