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
struct TYPE_3__ {int /*<<< orphan*/  dynobj; } ;
struct ppc_link_hash_table {scalar_t__ got; TYPE_1__ elf; } ;
struct bfd_link_info {int dummy; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {int /*<<< orphan*/ * relgot; int /*<<< orphan*/ * got; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_elf_create_got_section (int /*<<< orphan*/ ,struct bfd_link_info*) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ppc64_elf_tdata (int /*<<< orphan*/ *) ; 
 struct ppc_link_hash_table* ppc_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
create_got_section (bfd *abfd, struct bfd_link_info *info)
{
  asection *got, *relgot;
  flagword flags;
  struct ppc_link_hash_table *htab = ppc_hash_table (info);

  if (!htab->got)
    {
      if (! _bfd_elf_create_got_section (htab->elf.dynobj, info))
	return FALSE;

      htab->got = bfd_get_section_by_name (htab->elf.dynobj, ".got");
      if (!htab->got)
	abort ();
    }

  flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS | SEC_IN_MEMORY
	   | SEC_LINKER_CREATED);

  got = bfd_make_section_anyway_with_flags (abfd, ".got", flags);
  if (!got
      || !bfd_set_section_alignment (abfd, got, 3))
    return FALSE;

  relgot = bfd_make_section_anyway_with_flags (abfd, ".rela.got",
					       flags | SEC_READONLY);
  if (!relgot
      || ! bfd_set_section_alignment (abfd, relgot, 3))
    return FALSE;

  ppc64_elf_tdata (abfd)->got = got;
  ppc64_elf_tdata (abfd)->relgot = relgot;
  return TRUE;
}