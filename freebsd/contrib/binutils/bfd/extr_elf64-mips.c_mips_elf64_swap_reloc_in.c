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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_type2; int /*<<< orphan*/  r_type3; int /*<<< orphan*/  r_ssym; int /*<<< orphan*/  r_sym; int /*<<< orphan*/  r_offset; } ;
struct TYPE_5__ {scalar_t__ r_addend; void* r_type; void* r_type2; void* r_type3; void* r_ssym; int /*<<< orphan*/  r_sym; int /*<<< orphan*/  r_offset; } ;
typedef  TYPE_1__ Elf64_Mips_Internal_Rela ;
typedef  TYPE_2__ Elf64_Mips_External_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_GET_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_elf64_swap_reloc_in (bfd *abfd, const Elf64_Mips_External_Rel *src,
			  Elf64_Mips_Internal_Rela *dst)
{
  dst->r_offset = H_GET_64 (abfd, src->r_offset);
  dst->r_sym = H_GET_32 (abfd, src->r_sym);
  dst->r_ssym = H_GET_8 (abfd, src->r_ssym);
  dst->r_type3 = H_GET_8 (abfd, src->r_type3);
  dst->r_type2 = H_GET_8 (abfd, src->r_type2);
  dst->r_type = H_GET_8 (abfd, src->r_type);
  dst->r_addend = 0;
}