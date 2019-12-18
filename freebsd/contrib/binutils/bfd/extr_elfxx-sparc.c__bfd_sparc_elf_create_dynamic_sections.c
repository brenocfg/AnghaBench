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
struct bfd_link_info {scalar_t__ shared; } ;
struct _bfd_sparc_elf_link_hash_table {int plt_header_size; int plt_entry_size; void* srelbss; void* sdynbss; void* srelplt; void* splt; int /*<<< orphan*/  build_plt_entry; int /*<<< orphan*/  srelplt2; scalar_t__ is_vxworks; int /*<<< orphan*/  sgot; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ ABI_64_P (int /*<<< orphan*/ *) ; 
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int PLT32_ENTRY_SIZE ; 
 int PLT32_HEADER_SIZE ; 
 int PLT64_ENTRY_SIZE ; 
 int PLT64_HEADER_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 struct _bfd_sparc_elf_link_hash_table* _bfd_sparc_elf_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  abort () ; 
 void* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  create_got_section (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  elf_vxworks_create_dynamic_sections (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc32_plt_entry_build ; 
 int /*<<< orphan*/  sparc64_plt_entry_build ; 
 int /*<<< orphan*/  sparc_vxworks_exec_plt0_entry ; 
 int /*<<< orphan*/  sparc_vxworks_exec_plt_entry ; 
 int /*<<< orphan*/  sparc_vxworks_shared_plt0_entry ; 
 int /*<<< orphan*/  sparc_vxworks_shared_plt_entry ; 

bfd_boolean
_bfd_sparc_elf_create_dynamic_sections (bfd *dynobj,
					struct bfd_link_info *info)
{
  struct _bfd_sparc_elf_link_hash_table *htab;

  htab = _bfd_sparc_elf_hash_table (info);
  if (!htab->sgot && !create_got_section (dynobj, info))
    return FALSE;

  if (!_bfd_elf_create_dynamic_sections (dynobj, info))
    return FALSE;

  htab->splt = bfd_get_section_by_name (dynobj, ".plt");
  htab->srelplt = bfd_get_section_by_name (dynobj, ".rela.plt");
  htab->sdynbss = bfd_get_section_by_name (dynobj, ".dynbss");
  if (!info->shared)
    htab->srelbss = bfd_get_section_by_name (dynobj, ".rela.bss");

  if (htab->is_vxworks)
    {
      if (!elf_vxworks_create_dynamic_sections (dynobj, info, &htab->srelplt2))
	return FALSE;
      if (info->shared)
	{
	  htab->plt_header_size
	    = 4 * ARRAY_SIZE (sparc_vxworks_shared_plt0_entry);
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (sparc_vxworks_shared_plt_entry);
	}
      else
	{
	  htab->plt_header_size
	    = 4 * ARRAY_SIZE (sparc_vxworks_exec_plt0_entry);
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (sparc_vxworks_exec_plt_entry);
	}
    }
  else
    {
      if (ABI_64_P (dynobj))
	{
	  htab->build_plt_entry = sparc64_plt_entry_build;
	  htab->plt_header_size = PLT64_HEADER_SIZE;
	  htab->plt_entry_size = PLT64_ENTRY_SIZE;
	}
      else
	{
	  htab->build_plt_entry = sparc32_plt_entry_build;
	  htab->plt_header_size = PLT32_HEADER_SIZE;
	  htab->plt_entry_size = PLT32_ENTRY_SIZE;
	}
    }

  if (!htab->splt || !htab->srelplt || !htab->sdynbss
      || (!info->shared && !htab->srelbss))
    abort ();

  return TRUE;
}