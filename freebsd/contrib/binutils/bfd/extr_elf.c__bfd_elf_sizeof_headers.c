#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf_segment_map {struct elf_segment_map* next; } ;
struct elf_backend_data {TYPE_1__* s; } ;
struct bfd_link_info {int /*<<< orphan*/  relocatable; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {scalar_t__ program_header_size; struct elf_segment_map* segment_map; } ;
struct TYPE_3__ {int sizeof_ehdr; scalar_t__ sizeof_phdr; } ;

/* Variables and functions */
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 scalar_t__ get_program_header_size (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

int
_bfd_elf_sizeof_headers (bfd *abfd, struct bfd_link_info *info)
{
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);
  int ret = bed->s->sizeof_ehdr;

  if (!info->relocatable)
    {
      bfd_size_type phdr_size = elf_tdata (abfd)->program_header_size;

      if (phdr_size == (bfd_size_type) -1)
	{
	  struct elf_segment_map *m;

	  phdr_size = 0;
	  for (m = elf_tdata (abfd)->segment_map; m != NULL; m = m->next)
	    phdr_size += bed->s->sizeof_phdr;

	  if (phdr_size == 0)
	    phdr_size = get_program_header_size (abfd, info);
	}

      elf_tdata (abfd)->program_header_size = phdr_size;
      ret += phdr_size;
    }

  return ret;
}