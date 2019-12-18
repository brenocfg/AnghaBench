#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {struct bfd_elf_special_section const* special_sections; } ;
typedef  struct bfd_elf_special_section const bfd_elf_special_section ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  use_rela_p; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 struct bfd_elf_special_section const* _bfd_elf_get_special_section (char*,struct bfd_elf_special_section const*,int /*<<< orphan*/ ) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 struct bfd_elf_special_section const** special_sections ; 

const struct bfd_elf_special_section *
_bfd_elf_get_sec_type_attr (bfd *abfd, asection *sec)
{
  int i;
  const struct bfd_elf_special_section *spec;
  const struct elf_backend_data *bed;

  /* See if this is one of the special sections.  */
  if (sec->name == NULL)
    return NULL;

  bed = get_elf_backend_data (abfd);
  spec = bed->special_sections;
  if (spec)
    {
      spec = _bfd_elf_get_special_section (sec->name,
					   bed->special_sections,
					   sec->use_rela_p);
      if (spec != NULL)
	return spec;
    }

  if (sec->name[0] != '.')
    return NULL;

  i = sec->name[1] - 'b';
  if (i < 0 || i > 't' - 'b')
    return NULL;

  spec = special_sections[i];

  if (spec == NULL)
    return NULL;

  return _bfd_elf_get_special_section (sec->name, spec, sec->use_rela_p);
}