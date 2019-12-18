#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {scalar_t__ r_offset; void* r_type3; int /*<<< orphan*/  r_ssym; void* r_type2; int /*<<< orphan*/  r_sym; void* r_type; } ;
struct TYPE_5__ {scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf_Internal_Rela ;
typedef  TYPE_2__ Elf64_Mips_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf64_Mips_External_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  ELF64_MIPS_R_SSYM (int /*<<< orphan*/ ) ; 
 void* ELF64_MIPS_R_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_elf64_swap_reloc_out (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mips_elf64_be_swap_reloc_out (bfd *abfd, const Elf_Internal_Rela *src,
			      bfd_byte *dst)
{
  Elf64_Mips_Internal_Rela mirel;

  mirel.r_offset = src[0].r_offset;
  BFD_ASSERT(src[0].r_offset == src[1].r_offset);

  mirel.r_type = ELF64_MIPS_R_TYPE (src[0].r_info);
  mirel.r_sym = ELF64_R_SYM (src[0].r_info);
  mirel.r_type2 = ELF64_MIPS_R_TYPE (src[1].r_info);
  mirel.r_ssym = ELF64_MIPS_R_SSYM (src[1].r_info);
  mirel.r_type3 = ELF64_MIPS_R_TYPE (src[2].r_info);

  mips_elf64_swap_reloc_out (abfd, &mirel,
			     (Elf64_Mips_External_Rel *) dst);
}