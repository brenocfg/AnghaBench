#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i; } ;
struct TYPE_6__ {int tag; TYPE_1__ attr; struct TYPE_6__* next; } ;
typedef  TYPE_2__ obj_attribute_list ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int i; } ;

/* Variables and functions */
 int NUM_KNOWN_OBJ_ATTRIBUTES ; 
 TYPE_4__** elf_known_obj_attributes (int /*<<< orphan*/ *) ; 
 TYPE_2__** elf_other_obj_attributes (int /*<<< orphan*/ *) ; 

int
bfd_elf_get_obj_attr_int (bfd *abfd, int vendor, int tag)
{
  obj_attribute_list *p;

  if (tag < NUM_KNOWN_OBJ_ATTRIBUTES)
    {
      /* Knwon tags are preallocated.  */
      return elf_known_obj_attributes (abfd)[vendor][tag].i;
    }
  else
    {
      for (p = elf_other_obj_attributes (abfd)[vendor];
	   p;
	   p = p->next)
	{
	  if (tag == p->tag)
	    return p->attr.i;
	  if (tag < p->tag)
	    break;
	}
      return 0;
    }
}