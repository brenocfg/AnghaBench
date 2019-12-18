#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct elf_internal_shdr {size_t sh_name; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  e_shstrndx; } ;
typedef  struct elf_internal_shdr Elf_Internal_Shdr ;

/* Variables and functions */
 char* bfd_elf_get_str_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 
 struct elf_internal_shdr** elf_elfsections (int /*<<< orphan*/ *) ; 
 unsigned int elf_numsections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

struct elf_internal_shdr *
bfd_elf_find_section (bfd *abfd, char *name)
{
  Elf_Internal_Shdr **i_shdrp;
  char *shstrtab;
  unsigned int max;
  unsigned int i;

  i_shdrp = elf_elfsections (abfd);
  if (i_shdrp != NULL)
    {
      shstrtab = bfd_elf_get_str_section (abfd,
					  elf_elfheader (abfd)->e_shstrndx);
      if (shstrtab != NULL)
	{
	  max = elf_numsections (abfd);
	  for (i = 1; i < max; i++)
	    if (!strcmp (&shstrtab[i_shdrp[i]->sh_name], name))
	      return i_shdrp[i];
	}
    }
  return 0;
}