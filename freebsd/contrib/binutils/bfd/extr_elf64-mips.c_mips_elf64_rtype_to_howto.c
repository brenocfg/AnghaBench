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
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 unsigned int R_MIPS16_max ; 
 unsigned int R_MIPS16_min ; 
#define  R_MIPS_GNU_REL16_S2 130 
#define  R_MIPS_GNU_VTENTRY 129 
#define  R_MIPS_GNU_VTINHERIT 128 
 scalar_t__ R_MIPS_max ; 
 int /*<<< orphan*/  elf_mips_gnu_rel16_s2 ; 
 int /*<<< orphan*/  elf_mips_gnu_rela16_s2 ; 
 int /*<<< orphan*/  elf_mips_gnu_vtentry_howto ; 
 int /*<<< orphan*/  elf_mips_gnu_vtinherit_howto ; 
 int /*<<< orphan*/ * mips16_elf64_howto_table_rel ; 
 int /*<<< orphan*/ * mips16_elf64_howto_table_rela ; 
 int /*<<< orphan*/ * mips_elf64_howto_table_rel ; 
 int /*<<< orphan*/ * mips_elf64_howto_table_rela ; 

__attribute__((used)) static reloc_howto_type *
mips_elf64_rtype_to_howto (unsigned int r_type, bfd_boolean rela_p)
{
  switch (r_type)
    {
    case R_MIPS_GNU_VTINHERIT:
      return &elf_mips_gnu_vtinherit_howto;
    case R_MIPS_GNU_VTENTRY:
      return &elf_mips_gnu_vtentry_howto;
    case R_MIPS_GNU_REL16_S2:
      if (rela_p)
	return &elf_mips_gnu_rela16_s2;
      else
	return &elf_mips_gnu_rel16_s2;
    default:
      if (r_type >= R_MIPS16_min && r_type < R_MIPS16_max)
	{
	  if (rela_p)
	    return &mips16_elf64_howto_table_rela[r_type - R_MIPS16_min];
	  else
	    return &mips16_elf64_howto_table_rel[r_type - R_MIPS16_min];
	}
      BFD_ASSERT (r_type < (unsigned int) R_MIPS_max);
      if (rela_p)
	return &mips_elf64_howto_table_rela[r_type];
      else
	return &mips_elf64_howto_table_rel[r_type];
      break;
    }
}