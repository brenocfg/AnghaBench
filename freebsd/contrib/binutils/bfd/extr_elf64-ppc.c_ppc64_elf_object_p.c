#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_8__ {TYPE_1__* arch_info; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_9__ {scalar_t__* e_ident; } ;
struct TYPE_7__ {int bits_per_word; struct TYPE_7__* next; scalar_t__ the_default; } ;
typedef  TYPE_3__ Elf_Internal_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS64 ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* elf_elfheader (TYPE_2__*) ; 

__attribute__((used)) static bfd_boolean
ppc64_elf_object_p (bfd *abfd)
{
  if (abfd->arch_info->the_default && abfd->arch_info->bits_per_word == 32)
    {
      Elf_Internal_Ehdr *i_ehdr = elf_elfheader (abfd);

      if (i_ehdr->e_ident[EI_CLASS] == ELFCLASS64)
	{
	  /* Relies on arch after 32 bit default being 64 bit default.  */
	  abfd->arch_info = abfd->arch_info->next;
	  BFD_ASSERT (abfd->arch_info->bits_per_word == 64);
	}
    }
  return TRUE;
}