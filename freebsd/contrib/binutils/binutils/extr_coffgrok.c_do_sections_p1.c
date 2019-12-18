#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct coff_section {char* name; int code; int data; int number; scalar_t__ size; scalar_t__ address; TYPE_1__* bfd_section; struct coff_reloc* relocs; scalar_t__ nrelocs; } ;
struct coff_reloc {int dummy; } ;
struct coff_ofile {struct coff_section* sections; scalar_t__ nsections; } ;
struct TYPE_9__ {int target_index; int flags; scalar_t__ reloc_count; scalar_t__ lma; scalar_t__ name; struct TYPE_9__* next; } ;
typedef  TYPE_1__ asection ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_10__ {TYPE_1__* sections; scalar_t__ section_count; } ;

/* Variables and functions */
 int SEC_CODE ; 
 int SEC_DATA ; 
 TYPE_3__* abfd ; 
 long bfd_canonicalize_reloc (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (TYPE_3__*) ; 
 long bfd_get_reloc_upper_bound (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ bfd_get_section_size (TYPE_1__*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  syms ; 
 scalar_t__ xcalloc (scalar_t__,int) ; 
 scalar_t__ xmalloc (long) ; 

__attribute__((used)) static void
do_sections_p1 (struct coff_ofile *head)
{
  asection *section;
  int idx;
  struct coff_section *all = (struct coff_section *) (xcalloc (abfd->section_count + 1,
					     sizeof (struct coff_section)));
  head->nsections = abfd->section_count + 1;
  head->sections = all;

  for (idx = 0, section = abfd->sections; section; section = section->next, idx++)
    {
      long relsize;
      int i = section->target_index;
      arelent **relpp;
      long relcount;

      relsize = bfd_get_reloc_upper_bound (abfd, section);
      if (relsize < 0)
	bfd_fatal (bfd_get_filename (abfd));
      if (relsize == 0)
	continue;
      relpp = (arelent **) xmalloc (relsize);
      relcount = bfd_canonicalize_reloc (abfd, section, relpp, syms);
      if (relcount < 0)
	bfd_fatal (bfd_get_filename (abfd));

      head->sections[i].name = (char *) (section->name);
      head->sections[i].code = section->flags & SEC_CODE;
      head->sections[i].data = section->flags & SEC_DATA;
      if (strcmp (section->name, ".bss") == 0)
	head->sections[i].data = 1;
      head->sections[i].address = section->lma;
      head->sections[i].size = bfd_get_section_size (section);
      head->sections[i].number = idx;
      head->sections[i].nrelocs = section->reloc_count;
      head->sections[i].relocs =
	(struct coff_reloc *) (xcalloc (section->reloc_count,
					sizeof (struct coff_reloc)));
      head->sections[i].bfd_section = section;
    }
  head->sections[0].name = "ABSOLUTE";
  head->sections[0].code = 0;
  head->sections[0].data = 0;
  head->sections[0].address = 0;
  head->sections[0].size = 0;
  head->sections[0].number = 0;
}