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
struct TYPE_5__ {int type; unsigned int i; int /*<<< orphan*/  s; } ;
struct TYPE_6__ {scalar_t__ tag; struct TYPE_6__* next; TYPE_1__ attr; } ;
typedef  TYPE_2__ obj_attribute_list ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ Tag_compatibility ; 
 int /*<<< orphan*/  _bfd_elf_attr_strdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ bfd_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__** elf_other_obj_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

void
bfd_elf_add_obj_attr_compat (bfd *abfd, int vendor, unsigned int i,
			     const char *s)
{
  obj_attribute_list *list;
  obj_attribute_list *p;
  obj_attribute_list **lastp;

  list = (obj_attribute_list *)
    bfd_alloc (abfd, sizeof (obj_attribute_list));
  memset (list, 0, sizeof (obj_attribute_list));
  list->tag = Tag_compatibility;
  list->attr.type = 3;
  list->attr.i = i;
  list->attr.s = _bfd_elf_attr_strdup (abfd, s);

  lastp = &elf_other_obj_attributes (abfd)[vendor];
  for (p = *lastp; p; p = p->next)
    {
      int cmp;
      if (p->tag != Tag_compatibility)
	break;
      cmp = strcmp(s, p->attr.s);
      if (cmp < 0 || (cmp == 0 && i < p->attr.i))
	break;
      lastp = &p->next;
    }
  list->next = *lastp;
  *lastp = list;
}