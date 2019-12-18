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
struct ppc_link_hash_table {int /*<<< orphan*/ * relbrlt; int /*<<< orphan*/ * brlt; int /*<<< orphan*/ * glink; int /*<<< orphan*/ * sfpr; } ;
struct bfd_link_info {int /*<<< orphan*/  shared; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 void* bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
create_linkage_sections (bfd *dynobj, struct bfd_link_info *info)
{
  struct ppc_link_hash_table *htab;
  flagword flags;

  htab = ppc_hash_table (info);

  /* Create .sfpr for code to save and restore fp regs.  */
  flags = (SEC_ALLOC | SEC_LOAD | SEC_CODE | SEC_READONLY
	   | SEC_HAS_CONTENTS | SEC_IN_MEMORY | SEC_LINKER_CREATED);
  htab->sfpr = bfd_make_section_anyway_with_flags (dynobj, ".sfpr",
						   flags);
  if (htab->sfpr == NULL
      || ! bfd_set_section_alignment (dynobj, htab->sfpr, 2))
    return FALSE;

  /* Create .glink for lazy dynamic linking support.  */
  htab->glink = bfd_make_section_anyway_with_flags (dynobj, ".glink",
						    flags);
  if (htab->glink == NULL
      || ! bfd_set_section_alignment (dynobj, htab->glink, 3))
    return FALSE;

  /* Create branch lookup table for plt_branch stubs.  */
  flags = (SEC_ALLOC | SEC_LOAD
	   | SEC_HAS_CONTENTS | SEC_IN_MEMORY | SEC_LINKER_CREATED);
  htab->brlt = bfd_make_section_anyway_with_flags (dynobj, ".branch_lt",
						   flags);
  if (htab->brlt == NULL
      || ! bfd_set_section_alignment (dynobj, htab->brlt, 3))
    return FALSE;

  if (!info->shared)
    return TRUE;

  flags = (SEC_ALLOC | SEC_LOAD | SEC_READONLY
	   | SEC_HAS_CONTENTS | SEC_IN_MEMORY | SEC_LINKER_CREATED);
  htab->relbrlt = bfd_make_section_anyway_with_flags (dynobj,
						      ".rela.branch_lt",
						      flags);
  if (!htab->relbrlt
      || ! bfd_set_section_alignment (dynobj, htab->relbrlt, 3))
    return FALSE;

  return TRUE;
}