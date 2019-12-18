#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {TYPE_1__* hash; TYPE_2__* input_bfds; } ;
struct TYPE_6__ {scalar_t__ xvec; TYPE_3__* sections; struct TYPE_6__* link_next; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_7__ {int flags; scalar_t__ lineno_count; scalar_t__ reloc_count; scalar_t__ size; int /*<<< orphan*/  name; struct TYPE_7__* next; } ;
typedef  TYPE_3__ asection ;
struct TYPE_8__ {TYPE_3__* descriptor_section; TYPE_3__* toc_section; TYPE_3__* linkage_section; TYPE_3__* loader_section; TYPE_3__* debug_section; } ;
struct TYPE_5__ {scalar_t__ creator; } ;

/* Variables and functions */
 int SEC_MARK ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* xcoff_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static void
xcoff_sweep (struct bfd_link_info *info)
{
  bfd *sub;

  for (sub = info->input_bfds; sub != NULL; sub = sub->link_next)
    {
      asection *o;

      for (o = sub->sections; o != NULL; o = o->next)
	{
	  if ((o->flags & SEC_MARK) == 0)
	    {
	      /* Keep all sections from non-XCOFF input files.  Keep
		 special sections.  Keep .debug sections for the
		 moment.  */
	      if (sub->xvec != info->hash->creator
		  || o == xcoff_hash_table (info)->debug_section
		  || o == xcoff_hash_table (info)->loader_section
		  || o == xcoff_hash_table (info)->linkage_section
		  || o == xcoff_hash_table (info)->toc_section
		  || o == xcoff_hash_table (info)->descriptor_section
		  || strcmp (o->name, ".debug") == 0)
		o->flags |= SEC_MARK;
	      else
		{
		  o->size = 0;
		  o->reloc_count = 0;
		  o->lineno_count = 0;
		}
	    }
	}
    }
}