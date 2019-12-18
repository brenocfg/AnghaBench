#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_9__ {scalar_t__ output_has_begun; TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_10__ {int flags; scalar_t__ size; scalar_t__ lma; scalar_t__ filepos; struct TYPE_10__* next; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 int SEC_NEVER_LOAD ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ _bfd_generic_set_section_contents (TYPE_1__*,TYPE_2__*,void const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bfd_get_section_name (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bfd_boolean
binary_set_section_contents (bfd *abfd,
			     asection *sec,
			     const void * data,
			     file_ptr offset,
			     bfd_size_type size)
{
  if (size == 0)
    return TRUE;

  if (! abfd->output_has_begun)
    {
      bfd_boolean found_low;
      bfd_vma low;
      asection *s;

      /* The lowest section LMA sets the virtual address of the start
         of the file.  We use this to set the file position of all the
         sections.  */
      found_low = FALSE;
      low = 0;
      for (s = abfd->sections; s != NULL; s = s->next)
	if (((s->flags
	      & (SEC_HAS_CONTENTS | SEC_LOAD | SEC_ALLOC | SEC_NEVER_LOAD))
	     == (SEC_HAS_CONTENTS | SEC_LOAD | SEC_ALLOC))
	    && (s->size > 0)
	    && (! found_low || s->lma < low))
	  {
	    low = s->lma;
	    found_low = TRUE;
	  }

      for (s = abfd->sections; s != NULL; s = s->next)
	{
	  s->filepos = s->lma - low;

	  /* Skip following warning check for sections that will not
	     occupy file space.  */
	  if ((s->flags
	       & (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_NEVER_LOAD))
	      != (SEC_HAS_CONTENTS | SEC_ALLOC)
	      || (s->size == 0))
	    continue;

	  /* If attempting to generate a binary file from a bfd with
	     LMA's all over the place, huge (sparse?) binary files may
	     result.  This condition attempts to detect this situation
	     and print a warning.  Better heuristics would be nice to
	     have.  */

	  if (s->filepos < 0)
	    (*_bfd_error_handler)
	      (_("Warning: Writing section `%s' to huge (ie negative) file offset 0x%lx."),
	       bfd_get_section_name (abfd, s),
	       (unsigned long) s->filepos);
	}

      abfd->output_has_begun = TRUE;
    }

  /* We don't want to output anything for a section that is neither
     loaded nor allocated.  The contents of such a section are not
     meaningful in the binary format.  */
  if ((sec->flags & (SEC_LOAD | SEC_ALLOC)) == 0)
    return TRUE;
  if ((sec->flags & SEC_NEVER_LOAD) != 0)
    return TRUE;

  return _bfd_generic_set_section_contents (abfd, sec, data, offset, size);
}