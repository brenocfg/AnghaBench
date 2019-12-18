#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tag; int /*<<< orphan*/  attr; struct TYPE_3__* next; } ;
typedef  TYPE_1__ obj_attribute_list ;
typedef  int /*<<< orphan*/  obj_attribute ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int NUM_KNOWN_OBJ_ATTRIBUTES ; 
 int /*<<< orphan*/  Tag_File ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** elf_known_obj_attributes (int /*<<< orphan*/ *) ; 
 TYPE_1__** elf_other_obj_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int strlen (char const*) ; 
 char* vendor_obj_attr_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * write_obj_attribute (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vendor_set_obj_attr_contents (bfd *abfd, bfd_byte *contents, bfd_vma size,
			      int vendor)
{
  bfd_byte *p;
  obj_attribute *attr;
  obj_attribute_list *list;
  int i;
  const char *vendor_name = vendor_obj_attr_name (abfd, vendor);
  size_t vendor_length = strlen (vendor_name) + 1;

  p = contents;
  bfd_put_32 (abfd, size, p);
  p += 4;
  memcpy (p, vendor_name, vendor_length);
  p += vendor_length;
  *(p++) = Tag_File;
  bfd_put_32 (abfd, size - 4 - vendor_length, p);
  p += 4;

  attr = elf_known_obj_attributes (abfd)[vendor];
  for (i = 4; i < NUM_KNOWN_OBJ_ATTRIBUTES; i++)
    p = write_obj_attribute (p, i, &attr[i]);

  for (list = elf_other_obj_attributes (abfd)[vendor];
       list;
       list = list->next)
    p = write_obj_attribute (p, list->tag, &list->attr);
}