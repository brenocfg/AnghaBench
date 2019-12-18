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
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int NUM_KNOWN_OBJ_ATTRIBUTES ; 
 int OBJ_ATTR_PROC ; 
 int /*<<< orphan*/ ** elf_known_obj_attributes (int /*<<< orphan*/ *) ; 
 TYPE_1__** elf_other_obj_attributes (int /*<<< orphan*/ *) ; 
 scalar_t__ obj_attr_size (int,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 char* vendor_obj_attr_name (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bfd_vma
vendor_obj_attr_size (bfd *abfd, int vendor)
{
  bfd_vma size;
  obj_attribute *attr;
  obj_attribute_list *list;
  int i;
  const char *vendor_name = vendor_obj_attr_name (abfd, vendor);

  if (!vendor_name)
    return 0;

  attr = elf_known_obj_attributes (abfd)[vendor];
  size = 0;
  for (i = 4; i < NUM_KNOWN_OBJ_ATTRIBUTES; i++)
    size += obj_attr_size (i, &attr[i]);

  for (list = elf_other_obj_attributes (abfd)[vendor];
       list;
       list = list->next)
    size += obj_attr_size (list->tag, &list->attr);

  /* <size> <vendor_name> NUL 0x1 <size> */
  return ((size || vendor == OBJ_ATTR_PROC)
	  ? size + 10 + strlen (vendor_name)
	  : 0);
}