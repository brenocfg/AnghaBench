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
struct TYPE_6__ {int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_type2; int /*<<< orphan*/  r_type3; int /*<<< orphan*/  r_ssym; int /*<<< orphan*/  r_sym; int /*<<< orphan*/  r_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  r_addend; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_type2; int /*<<< orphan*/  r_type3; int /*<<< orphan*/  r_ssym; int /*<<< orphan*/  r_sym; int /*<<< orphan*/  r_offset; } ;
typedef  TYPE_1__ Elf64_Mips_Internal_Rela ;
typedef  TYPE_2__ Elf64_Mips_External_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_S64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_elf64_swap_reloca_out (bfd *abfd, const Elf64_Mips_Internal_Rela *src,
			    Elf64_Mips_External_Rela *dst)
{
  H_PUT_64 (abfd, src->r_offset, dst->r_offset);
  H_PUT_32 (abfd, src->r_sym, dst->r_sym);
  H_PUT_8 (abfd, src->r_ssym, dst->r_ssym);
  H_PUT_8 (abfd, src->r_type3, dst->r_type3);
  H_PUT_8 (abfd, src->r_type2, dst->r_type2);
  H_PUT_8 (abfd, src->r_type, dst->r_type);
  H_PUT_S64 (abfd, src->r_addend, dst->r_addend);
}