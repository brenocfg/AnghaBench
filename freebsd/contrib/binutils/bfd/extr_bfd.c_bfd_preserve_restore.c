#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfd_preserve {int /*<<< orphan*/ * marker; int /*<<< orphan*/  section_count; int /*<<< orphan*/  section_last; int /*<<< orphan*/  sections; int /*<<< orphan*/  section_htab; int /*<<< orphan*/  flags; int /*<<< orphan*/  arch_info; int /*<<< orphan*/  tdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  any; } ;
struct TYPE_6__ {int /*<<< orphan*/  section_count; int /*<<< orphan*/  section_last; int /*<<< orphan*/  sections; int /*<<< orphan*/  section_htab; int /*<<< orphan*/  flags; int /*<<< orphan*/  arch_info; TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_release (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
bfd_preserve_restore (bfd *abfd, struct bfd_preserve *preserve)
{
  bfd_hash_table_free (&abfd->section_htab);

  abfd->tdata.any = preserve->tdata;
  abfd->arch_info = preserve->arch_info;
  abfd->flags = preserve->flags;
  abfd->section_htab = preserve->section_htab;
  abfd->sections = preserve->sections;
  abfd->section_last = preserve->section_last;
  abfd->section_count = preserve->section_count;

  /* bfd_release frees all memory more recently bfd_alloc'd than
     its arg, as well as its arg.  */
  if (preserve->marker != NULL)
    {
      bfd_release (abfd, preserve->marker);
      preserve->marker = NULL;
    }
}