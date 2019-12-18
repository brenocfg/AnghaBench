#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* bfd_section; } ;
typedef  TYPE_2__ lang_output_section_statement_type ;
struct TYPE_8__ {scalar_t__ current; scalar_t__ origin; scalar_t__ length; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ lang_memory_region_type ;
typedef  int /*<<< orphan*/  etree_type ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
os_region_check (lang_output_section_statement_type *os,
		 lang_memory_region_type *region,
		 etree_type *tree,
		 bfd_vma base)
{
  if ((region->current < region->origin
       || (region->current - region->origin > region->length))
      && ((region->current != region->origin + region->length)
	  || base == 0))
    {
      if (tree != NULL)
	{
	  einfo (_("%X%P: address 0x%v of %B section %s"
		   " is not within region %s\n"),
		 region->current,
		 os->bfd_section->owner,
		 os->bfd_section->name,
		 region->name);
	}
      else
	{
	  einfo (_("%X%P: region %s is full (%B section %s)\n"),
		 region->name,
		 os->bfd_section->owner,
		 os->bfd_section->name);
	}
      /* Reset the region pointer.  */
      region->current = region->origin;
    }
}