#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sec_ptr ;
typedef  int file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int flags; void* contents; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_DEBUGGING ; 
 int /*<<< orphan*/  TRUE ; 
 void* bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_3__* ieee_per_section (TYPE_1__*) ; 
 int /*<<< orphan*/  init_for_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_set_section_contents (bfd *abfd,
			   sec_ptr section,
			   const void * location,
			   file_ptr offset,
			   bfd_size_type count)
{
  if ((section->flags & SEC_DEBUGGING) != 0)
    {
      if (section->contents == NULL)
	{
	  bfd_size_type size = section->size;
	  section->contents = bfd_alloc (abfd, size);
	  if (section->contents == NULL)
	    return FALSE;
	}
      /* bfd_set_section_contents has already checked that everything
         is within range.  */
      memcpy (section->contents + offset, location, (size_t) count);
      return TRUE;
    }

  if (ieee_per_section (section)->data == (bfd_byte *) NULL)
    {
      if (!init_for_output (abfd))
	return FALSE;
    }
  memcpy ((void *) (ieee_per_section (section)->data + offset),
	  (void *) location,
	  (unsigned int) count);
  return TRUE;
}