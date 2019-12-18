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
typedef  enum elf_ppc_reloc_type { ____Placeholder_elf_ppc_reloc_type } elf_ppc_reloc_type ;

/* Variables and functions */
#define  R_PPC_REL14 137 
#define  R_PPC_REL14_BRNTAKEN 136 
#define  R_PPC_REL14_BRTAKEN 135 
#define  R_PPC_REL24 134 
#define  R_PPC_REL32 133 
#define  R_PPC_TPREL16 132 
#define  R_PPC_TPREL16_HA 131 
#define  R_PPC_TPREL16_HI 130 
#define  R_PPC_TPREL16_LO 129 
#define  R_PPC_TPREL32 128 

__attribute__((used)) static int
must_be_dyn_reloc (struct bfd_link_info *info,
		   enum elf_ppc_reloc_type r_type)
{
  switch (r_type)
    {
    default:
      return 1;

    case R_PPC_REL24:
    case R_PPC_REL14:
    case R_PPC_REL14_BRTAKEN:
    case R_PPC_REL14_BRNTAKEN:
    case R_PPC_REL32:
      return 0;

    case R_PPC_TPREL32:
    case R_PPC_TPREL16:
    case R_PPC_TPREL16_LO:
    case R_PPC_TPREL16_HI:
    case R_PPC_TPREL16_HA:
      return !info->executable;
    }
}