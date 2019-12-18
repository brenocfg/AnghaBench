#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {int sign_extend_vma; } ;
struct TYPE_7__ {int /*<<< orphan*/  sh_entsize; int /*<<< orphan*/  sh_addralign; int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_offset; int /*<<< orphan*/  sh_addr; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_name; } ;
struct TYPE_6__ {int /*<<< orphan*/ * contents; int /*<<< orphan*/ * bfd_section; void* sh_entsize; void* sh_addralign; void* sh_info; void* sh_link; void* sh_size; void* sh_offset; void* sh_addr; void* sh_flags; void* sh_type; void* sh_name; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;
typedef  TYPE_2__ Elf_External_Shdr ;

/* Variables and functions */
 void* H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_SIGNED_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* get_elf_backend_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
elf_swap_shdr_in (bfd *abfd,
		  const Elf_External_Shdr *src,
		  Elf_Internal_Shdr *dst)
{
  int signed_vma = get_elf_backend_data (abfd)->sign_extend_vma;

  dst->sh_name = H_GET_32 (abfd, src->sh_name);
  dst->sh_type = H_GET_32 (abfd, src->sh_type);
  dst->sh_flags = H_GET_WORD (abfd, src->sh_flags);
  if (signed_vma)
    dst->sh_addr = H_GET_SIGNED_WORD (abfd, src->sh_addr);
  else
    dst->sh_addr = H_GET_WORD (abfd, src->sh_addr);
  dst->sh_offset = H_GET_WORD (abfd, src->sh_offset);
  dst->sh_size = H_GET_WORD (abfd, src->sh_size);
  dst->sh_link = H_GET_32 (abfd, src->sh_link);
  dst->sh_info = H_GET_32 (abfd, src->sh_info);
  dst->sh_addralign = H_GET_WORD (abfd, src->sh_addralign);
  dst->sh_entsize = H_GET_WORD (abfd, src->sh_entsize);
  dst->bfd_section = NULL;
  dst->contents = NULL;
}