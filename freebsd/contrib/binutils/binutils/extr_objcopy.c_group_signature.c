#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {TYPE_1__* s; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_9__ {int /*<<< orphan*/ * owner; } ;
typedef  TYPE_2__ asection ;
struct TYPE_10__ {size_t sh_link; scalar_t__ sh_type; int sh_info; int sh_size; } ;
struct TYPE_11__ {TYPE_3__ this_hdr; } ;
struct TYPE_8__ {int sizeof_sym; } ;
typedef  TYPE_3__ Elf_Internal_Shdr ;

/* Variables and functions */
 scalar_t__ SHT_SYMTAB ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_3__** elf_elfsections (int /*<<< orphan*/ *) ; 
 size_t elf_numsections (int /*<<< orphan*/ *) ; 
 TYPE_5__* elf_section_data (TYPE_2__*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** isympp ; 

__attribute__((used)) static asymbol *
group_signature (asection *group)
{
  bfd *abfd = group->owner;
  Elf_Internal_Shdr *ghdr;

  if (bfd_get_flavour (abfd) != bfd_target_elf_flavour)
    return NULL;

  ghdr = &elf_section_data (group)->this_hdr;
  if (ghdr->sh_link < elf_numsections (abfd))
    {
      const struct elf_backend_data *bed = get_elf_backend_data (abfd);
      Elf_Internal_Shdr *symhdr = elf_elfsections (abfd) [ghdr->sh_link];

      if (symhdr->sh_type == SHT_SYMTAB
	  && ghdr->sh_info < symhdr->sh_size / bed->s->sizeof_sym)
	return isympp[ghdr->sh_info - 1];
    }
  return NULL;
}