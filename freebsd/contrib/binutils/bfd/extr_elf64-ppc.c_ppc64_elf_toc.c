#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
struct TYPE_8__ {TYPE_3__* sections; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_9__ {int flags; scalar_t__ output_offset; TYPE_1__* output_section; struct TYPE_9__* next; } ;
typedef  TYPE_3__ asection ;
struct TYPE_7__ {scalar_t__ vma; } ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_READONLY ; 
 int SEC_SMALL_DATA ; 
 TYPE_3__* bfd_get_section_by_name (TYPE_2__*,char*) ; 

bfd_vma
ppc64_elf_toc (bfd *obfd)
{
  asection *s;
  bfd_vma TOCstart;

  /* The TOC consists of sections .got, .toc, .tocbss, .plt in that
     order.  The TOC starts where the first of these sections starts.  */
  s = bfd_get_section_by_name (obfd, ".got");
  if (s == NULL)
    s = bfd_get_section_by_name (obfd, ".toc");
  if (s == NULL)
    s = bfd_get_section_by_name (obfd, ".tocbss");
  if (s == NULL)
    s = bfd_get_section_by_name (obfd, ".plt");
  if (s == NULL)
    {
      /* This may happen for
	 o  references to TOC base (SYM@toc / TOC[tc0]) without a
	 .toc directive
	 o  bad linker script
	 o --gc-sections and empty TOC sections

	 FIXME: Warn user?  */

      /* Look for a likely section.  We probably won't even be
	 using TOCstart.  */
      for (s = obfd->sections; s != NULL; s = s->next)
	if ((s->flags & (SEC_ALLOC | SEC_SMALL_DATA | SEC_READONLY))
	    == (SEC_ALLOC | SEC_SMALL_DATA))
	  break;
      if (s == NULL)
	for (s = obfd->sections; s != NULL; s = s->next)
	  if ((s->flags & (SEC_ALLOC | SEC_SMALL_DATA))
	      == (SEC_ALLOC | SEC_SMALL_DATA))
	    break;
      if (s == NULL)
	for (s = obfd->sections; s != NULL; s = s->next)
	  if ((s->flags & (SEC_ALLOC | SEC_READONLY)) == SEC_ALLOC)
	    break;
      if (s == NULL)
	for (s = obfd->sections; s != NULL; s = s->next)
	  if ((s->flags & SEC_ALLOC) == SEC_ALLOC)
	    break;
    }

  TOCstart = 0;
  if (s != NULL)
    TOCstart = s->output_section->vma + s->output_offset;

  return TOCstart;
}