#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int value; TYPE_4__* section; } ;
struct TYPE_9__ {TYPE_1__ def; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct elf_link_hash_entry {scalar_t__ size; TYPE_3__ root; } ;
typedef  unsigned int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_11__ {unsigned int size; int /*<<< orphan*/  owner; } ;
typedef  TYPE_4__ asection ;

/* Variables and functions */
 unsigned int BFD_ALIGN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int bfd_get_section_alignment (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ ,TYPE_4__*,unsigned int) ; 

bfd_boolean
_bfd_elf_adjust_dynamic_copy (struct elf_link_hash_entry *h,
			      asection *dynbss)
{
  unsigned int power_of_two;
  bfd_vma mask;
  asection *sec = h->root.u.def.section;

  /* The section aligment of definition is the maximum alignment
     requirement of symbols defined in the section.  Since we don't
     know the symbol alignment requirement, we start with the
     maximum alignment and check low bits of the symbol address
     for the minimum alignment.  */
  power_of_two = bfd_get_section_alignment (sec->owner, sec);
  mask = ((bfd_vma) 1 << power_of_two) - 1;
  while ((h->root.u.def.value & mask) != 0)
    {
       mask >>= 1;
       --power_of_two;
    }

  if (power_of_two > bfd_get_section_alignment (dynbss->owner,
						dynbss))
    {
      /* Adjust the section alignment if needed.  */
      if (! bfd_set_section_alignment (dynbss->owner, dynbss,
				       power_of_two))
	return FALSE;
    }

  /* We make sure that the symbol will be aligned properly.  */
  dynbss->size = BFD_ALIGN (dynbss->size, mask + 1);

  /* Define the symbol as being at this point in DYNBSS.  */
  h->root.u.def.section = dynbss;
  h->root.u.def.value = dynbss->size;

  /* Increment the size of DYNBSS to make room for the symbol.  */
  dynbss->size += h->size;

  return TRUE;
}