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
struct TYPE_7__ {int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_shnum; int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_ehsize; int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_shoff; int /*<<< orphan*/  e_phoff; int /*<<< orphan*/  e_entry; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_ident; } ;
struct TYPE_6__ {unsigned int e_type; unsigned int e_machine; unsigned int e_ehsize; unsigned int e_phentsize; unsigned int e_phnum; unsigned int e_shentsize; unsigned int e_shnum; unsigned int e_shstrndx; int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_shoff; int /*<<< orphan*/  e_phoff; int /*<<< orphan*/  e_entry; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_ident; } ;
typedef  TYPE_1__ Elf_Internal_Ehdr ;
typedef  TYPE_2__ Elf_External_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  EI_NIDENT ; 
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_SIGNED_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int SHN_LORESERVE ; 
 unsigned int SHN_UNDEF ; 
 unsigned int SHN_XINDEX ; 
 TYPE_3__* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elf_swap_ehdr_out (bfd *abfd,
		   const Elf_Internal_Ehdr *src,
		   Elf_External_Ehdr *dst)
{
  unsigned int tmp;
  int signed_vma = get_elf_backend_data (abfd)->sign_extend_vma;
  memcpy (dst->e_ident, src->e_ident, EI_NIDENT);
  /* note that all elements of dst are *arrays of unsigned char* already...  */
  H_PUT_16 (abfd, src->e_type, dst->e_type);
  H_PUT_16 (abfd, src->e_machine, dst->e_machine);
  H_PUT_32 (abfd, src->e_version, dst->e_version);
  if (signed_vma)
    H_PUT_SIGNED_WORD (abfd, src->e_entry, dst->e_entry);
  else
    H_PUT_WORD (abfd, src->e_entry, dst->e_entry);
  H_PUT_WORD (abfd, src->e_phoff, dst->e_phoff);
  H_PUT_WORD (abfd, src->e_shoff, dst->e_shoff);
  H_PUT_32 (abfd, src->e_flags, dst->e_flags);
  H_PUT_16 (abfd, src->e_ehsize, dst->e_ehsize);
  H_PUT_16 (abfd, src->e_phentsize, dst->e_phentsize);
  H_PUT_16 (abfd, src->e_phnum, dst->e_phnum);
  H_PUT_16 (abfd, src->e_shentsize, dst->e_shentsize);
  tmp = src->e_shnum;
  if (tmp >= SHN_LORESERVE)
    tmp = SHN_UNDEF;
  H_PUT_16 (abfd, tmp, dst->e_shnum);
  tmp = src->e_shstrndx;
  if (tmp >= SHN_LORESERVE)
    tmp = SHN_XINDEX;
  H_PUT_16 (abfd, tmp, dst->e_shstrndx);
}