#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct section_hash_entry {int dummy; } ;
struct bfd_preserve {int /*<<< orphan*/  section_htab; scalar_t__ section_count; int /*<<< orphan*/ * section_last; int /*<<< orphan*/ * sections; int /*<<< orphan*/  flags; int /*<<< orphan*/ * arch_info; int /*<<< orphan*/ * tdata; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_4__ {int /*<<< orphan*/ * any; } ;
struct TYPE_5__ {scalar_t__ section_count; int /*<<< orphan*/ * section_last; int /*<<< orphan*/ * sections; int /*<<< orphan*/  flags; int /*<<< orphan*/ * arch_info; TYPE_1__ tdata; int /*<<< orphan*/  section_htab; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_IN_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_default_arch_struct ; 
 int /*<<< orphan*/  bfd_hash_table_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_section_hash_newfunc ; 

bfd_boolean
bfd_preserve_save (bfd *abfd, struct bfd_preserve *preserve)
{
  preserve->tdata = abfd->tdata.any;
  preserve->arch_info = abfd->arch_info;
  preserve->flags = abfd->flags;
  preserve->sections = abfd->sections;
  preserve->section_last = abfd->section_last;
  preserve->section_count = abfd->section_count;
  preserve->section_htab = abfd->section_htab;

  if (! bfd_hash_table_init (&abfd->section_htab, bfd_section_hash_newfunc,
			     sizeof (struct section_hash_entry)))
    return FALSE;

  abfd->tdata.any = NULL;
  abfd->arch_info = &bfd_default_arch_struct;
  abfd->flags &= BFD_IN_MEMORY;
  abfd->sections = NULL;
  abfd->section_last = NULL;
  abfd->section_count = 0;

  return TRUE;
}