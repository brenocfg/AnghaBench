#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elf64_x86_64_link_hash_table {void* srelbss; void* sdynbss; void* srelplt; void* splt; int /*<<< orphan*/  sgot; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  abort () ; 
 void* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  create_got_section (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 struct elf64_x86_64_link_hash_table* elf64_x86_64_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
elf64_x86_64_create_dynamic_sections (bfd *dynobj, struct bfd_link_info *info)
{
  struct elf64_x86_64_link_hash_table *htab;

  htab = elf64_x86_64_hash_table (info);
  if (!htab->sgot && !create_got_section (dynobj, info))
    return FALSE;

  if (!_bfd_elf_create_dynamic_sections (dynobj, info))
    return FALSE;

  htab->splt = bfd_get_section_by_name (dynobj, ".plt");
  htab->srelplt = bfd_get_section_by_name (dynobj, ".rela.plt");
  htab->sdynbss = bfd_get_section_by_name (dynobj, ".dynbss");
  if (!info->shared)
    htab->srelbss = bfd_get_section_by_name (dynobj, ".rela.bss");

  if (!htab->splt || !htab->srelplt || !htab->sdynbss
      || (!info->shared && !htab->srelbss))
    abort ();

  return TRUE;
}