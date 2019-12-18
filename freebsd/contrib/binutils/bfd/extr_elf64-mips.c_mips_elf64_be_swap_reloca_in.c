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
struct TYPE_6__ {int /*<<< orphan*/  r_type3; int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_type2; int /*<<< orphan*/  r_ssym; int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_sym; } ;
struct TYPE_5__ {int /*<<< orphan*/  r_addend; void* r_info; int /*<<< orphan*/  r_offset; } ;
typedef  TYPE_1__ Elf_Internal_Rela ;
typedef  TYPE_2__ Elf64_Mips_Internal_Rela ;
typedef  int /*<<< orphan*/  Elf64_Mips_External_Rela ;

/* Variables and functions */
 void* ELF64_R_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STN_UNDEF ; 
 int /*<<< orphan*/  mips_elf64_swap_reloca_in (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_2__*) ; 

__attribute__((used)) static void
mips_elf64_be_swap_reloca_in (bfd *abfd, const bfd_byte *src,
			      Elf_Internal_Rela *dst)
{
  Elf64_Mips_Internal_Rela mirela;

  mips_elf64_swap_reloca_in (abfd,
			     (const Elf64_Mips_External_Rela *) src,
			     &mirela);

  dst[0].r_offset = mirela.r_offset;
  dst[0].r_info = ELF64_R_INFO (mirela.r_sym, mirela.r_type);
  dst[0].r_addend = mirela.r_addend;
  dst[1].r_offset = mirela.r_offset;
  dst[1].r_info = ELF64_R_INFO (mirela.r_ssym, mirela.r_type2);
  dst[1].r_addend = 0;
  dst[2].r_offset = mirela.r_offset;
  dst[2].r_info = ELF64_R_INFO (STN_UNDEF, mirela.r_type3);
  dst[2].r_addend = 0;
}