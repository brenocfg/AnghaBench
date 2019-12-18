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
struct bfd_link_info {int /*<<< orphan*/  executable; } ;
typedef  enum elf_ppc64_reloc_type { ____Placeholder_elf_ppc64_reloc_type } elf_ppc64_reloc_type ;

/* Variables and functions */
#define  R_PPC64_REL30 141 
#define  R_PPC64_REL32 140 
#define  R_PPC64_REL64 139 
#define  R_PPC64_TPREL16 138 
#define  R_PPC64_TPREL16_DS 137 
#define  R_PPC64_TPREL16_HA 136 
#define  R_PPC64_TPREL16_HI 135 
#define  R_PPC64_TPREL16_HIGHER 134 
#define  R_PPC64_TPREL16_HIGHERA 133 
#define  R_PPC64_TPREL16_HIGHEST 132 
#define  R_PPC64_TPREL16_HIGHESTA 131 
#define  R_PPC64_TPREL16_LO 130 
#define  R_PPC64_TPREL16_LO_DS 129 
#define  R_PPC64_TPREL64 128 

__attribute__((used)) static int
must_be_dyn_reloc (struct bfd_link_info *info,
		   enum elf_ppc64_reloc_type r_type)
{
  switch (r_type)
    {
    default:
      return 1;

    case R_PPC64_REL32:
    case R_PPC64_REL64:
    case R_PPC64_REL30:
      return 0;

    case R_PPC64_TPREL16:
    case R_PPC64_TPREL16_LO:
    case R_PPC64_TPREL16_HI:
    case R_PPC64_TPREL16_HA:
    case R_PPC64_TPREL16_DS:
    case R_PPC64_TPREL16_LO_DS:
    case R_PPC64_TPREL16_HIGHER:
    case R_PPC64_TPREL16_HIGHERA:
    case R_PPC64_TPREL16_HIGHEST:
    case R_PPC64_TPREL16_HIGHESTA:
    case R_PPC64_TPREL64:
      return !info->executable;
    }
}