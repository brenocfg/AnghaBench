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
struct elf32_arm_link_hash_table {int plt_header_size; int plt_entry_size; void* srelbss; void* sdynbss; void* srelplt; void* splt; int /*<<< orphan*/  srelplt2; scalar_t__ vxworks_p; int /*<<< orphan*/  sgot; } ;
struct bfd_link_info {scalar_t__ shared; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 char* RELOC_SECTION (struct elf32_arm_link_hash_table*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  abort () ; 
 void* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  create_got_section (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 struct elf32_arm_link_hash_table* elf32_arm_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  elf32_arm_vxworks_exec_plt0_entry ; 
 int /*<<< orphan*/  elf32_arm_vxworks_exec_plt_entry ; 
 int /*<<< orphan*/  elf32_arm_vxworks_shared_plt_entry ; 
 int /*<<< orphan*/  elf_vxworks_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
elf32_arm_create_dynamic_sections (bfd *dynobj, struct bfd_link_info *info)
{
  struct elf32_arm_link_hash_table *htab;

  htab = elf32_arm_hash_table (info);
  if (!htab->sgot && !create_got_section (dynobj, info))
    return FALSE;

  if (!_bfd_elf_create_dynamic_sections (dynobj, info))
    return FALSE;

  htab->splt = bfd_get_section_by_name (dynobj, ".plt");
  htab->srelplt = bfd_get_section_by_name (dynobj,
					   RELOC_SECTION (htab, ".plt"));
  htab->sdynbss = bfd_get_section_by_name (dynobj, ".dynbss");
  if (!info->shared)
    htab->srelbss = bfd_get_section_by_name (dynobj,
					     RELOC_SECTION (htab, ".bss"));

  if (htab->vxworks_p)
    {
      if (!elf_vxworks_create_dynamic_sections (dynobj, info, &htab->srelplt2))
	return FALSE;

      if (info->shared)
	{
	  htab->plt_header_size = 0;
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (elf32_arm_vxworks_shared_plt_entry);
	}
      else
	{
	  htab->plt_header_size
	    = 4 * ARRAY_SIZE (elf32_arm_vxworks_exec_plt0_entry);
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (elf32_arm_vxworks_exec_plt_entry);
	}
    }

  if (!htab->splt 
      || !htab->srelplt
      || !htab->sdynbss
      || (!info->shared && !htab->srelbss))
    abort ();

  return TRUE;
}