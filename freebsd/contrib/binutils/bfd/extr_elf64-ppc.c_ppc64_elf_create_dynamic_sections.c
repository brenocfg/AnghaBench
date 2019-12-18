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
struct ppc_link_hash_table {void* relbss; void* dynbss; void* relplt; void* plt; void* got; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  abort () ; 
 void* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
ppc64_elf_create_dynamic_sections (bfd *dynobj, struct bfd_link_info *info)
{
  struct ppc_link_hash_table *htab;

  if (!_bfd_elf_create_dynamic_sections (dynobj, info))
    return FALSE;

  htab = ppc_hash_table (info);
  if (!htab->got)
    htab->got = bfd_get_section_by_name (dynobj, ".got");
  htab->plt = bfd_get_section_by_name (dynobj, ".plt");
  htab->relplt = bfd_get_section_by_name (dynobj, ".rela.plt");
  htab->dynbss = bfd_get_section_by_name (dynobj, ".dynbss");
  if (!info->shared)
    htab->relbss = bfd_get_section_by_name (dynobj, ".rela.bss");

  if (!htab->got || !htab->plt || !htab->relplt || !htab->dynbss
      || (!info->shared && !htab->relbss))
    abort ();

  return TRUE;
}