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
struct loadable_section {int adj_vma; TYPE_2__* section; } ;
struct dwarf2_debug {unsigned int loadable_section_count; struct loadable_section* loadable_sections; } ;
typedef  int bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_6__ {int vma; int flags; scalar_t__ rawsize; scalar_t__ size; int alignment_power; struct TYPE_6__* next; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_zalloc (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
place_sections (bfd *abfd, struct dwarf2_debug *stash)
{
  struct loadable_section *p;
  unsigned int i;

  if (stash->loadable_section_count != 0)
    {
      i = stash->loadable_section_count;
      p = stash->loadable_sections;
      for (; i > 0; i--, p++)
	p->section->vma = p->adj_vma;
    }
  else
    {
      asection *sect;
      bfd_vma last_vma = 0;
      bfd_size_type amt;
      struct loadable_section *p;

      i = 0;
      for (sect = abfd->sections; sect != NULL; sect = sect->next)
	{
	  bfd_size_type sz;

	  if (sect->vma != 0 || (sect->flags & SEC_LOAD) == 0)
	    continue;

	  sz = sect->rawsize ? sect->rawsize : sect->size;
	  if (sz == 0)
	    continue;

	  i++;
	}

      amt = i * sizeof (struct loadable_section);
      p = (struct loadable_section *) bfd_zalloc (abfd, amt);
      if (! p)
	return FALSE;

      stash->loadable_sections = p;
      stash->loadable_section_count = i;

      for (sect = abfd->sections; sect != NULL; sect = sect->next)
	{
	  bfd_size_type sz;

	  if (sect->vma != 0 || (sect->flags & SEC_LOAD) == 0)
	    continue;

	  sz = sect->rawsize ? sect->rawsize : sect->size;
	  if (sz == 0)
	    continue;

	  p->section = sect;
	  if (last_vma != 0)
	    {
	      /* Align the new address to the current section
		 alignment.  */
	      last_vma = ((last_vma
			   + ~((bfd_vma) -1 << sect->alignment_power))
			  & ((bfd_vma) -1 << sect->alignment_power));
	      sect->vma = last_vma;
	    }
	  p->adj_vma = sect->vma;
	  last_vma += sect->vma + sz;

	  p++;
	}
    }

  return TRUE;
}