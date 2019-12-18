#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {unsigned int e_shstrndx; } ;
struct TYPE_4__ {unsigned int sh_size; unsigned int sh_name; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned long,char*) ; 
 int /*<<< orphan*/ * bfd_elf_get_str_section (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_3__* elf_elfheader (int /*<<< orphan*/ *) ; 
 TYPE_1__** elf_elfsections (int /*<<< orphan*/ *) ; 
 unsigned int elf_numsections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned long,char*) ; 

char *
bfd_elf_string_from_elf_section (bfd *abfd,
				 unsigned int shindex,
				 unsigned int strindex)
{
  Elf_Internal_Shdr *hdr;

  if (strindex == 0)
    return "";

  if (elf_elfsections (abfd) == NULL || shindex >= elf_numsections (abfd))
    return NULL;

  hdr = elf_elfsections (abfd)[shindex];

  if (hdr->contents == NULL
      && bfd_elf_get_str_section (abfd, shindex) == NULL)
    return NULL;

  if (strindex >= hdr->sh_size)
    {
      unsigned int shstrndx = elf_elfheader(abfd)->e_shstrndx;
      (*_bfd_error_handler)
	(_("%B: invalid string offset %u >= %lu for section `%s'"),
	 abfd, strindex, (unsigned long) hdr->sh_size,
	 (shindex == shstrndx && strindex == hdr->sh_name
	  ? ".shstrtab"
	  : bfd_elf_string_from_elf_section (abfd, shstrndx, hdr->sh_name)));
      return "";
    }

  return ((char *) hdr->contents) + strindex;
}