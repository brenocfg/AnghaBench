#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bfd_in_memory {int size; int /*<<< orphan*/  buffer; } ;
typedef  scalar_t__ file_ptr ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
struct TYPE_7__ {int flags; int where; scalar_t__ direction; scalar_t__ format; scalar_t__ origin; TYPE_1__* iovec; int /*<<< orphan*/ * my_archive; struct bfd_in_memory* iostream; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_6__ {int (* bseek ) (TYPE_2__*,scalar_t__,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int BFD_IN_MEMORY ; 
 int EINVAL ; 
 int SEEK_CUR ; 
 int SEEK_SET ; 
 scalar_t__ bfd_archive ; 
 int /*<<< orphan*/  bfd_error_file_truncated ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_realloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_tell (TYPE_2__*) ; 
 scalar_t__ both_direction ; 
 int errno ; 
 int stub1 (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ write_direction ; 

int
bfd_seek (bfd *abfd, file_ptr position, int direction)
{
  int result;
  file_ptr file_position;
  /* For the time being, a BFD may not seek to it's end.  The problem
     is that we don't easily have a way to recognize the end of an
     element in an archive.  */

  BFD_ASSERT (direction == SEEK_SET || direction == SEEK_CUR);

  if (direction == SEEK_CUR && position == 0)
    return 0;

  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    {
      struct bfd_in_memory *bim;

      bim = abfd->iostream;

      if (direction == SEEK_SET)
	abfd->where = position;
      else
	abfd->where += position;

      if (abfd->where > bim->size)
	{
	  if ((abfd->direction == write_direction) ||
	      (abfd->direction == both_direction))
	    {
	      bfd_size_type newsize, oldsize;

	      oldsize = (bim->size + 127) & ~(bfd_size_type) 127;
	      bim->size = abfd->where;
	      /* Round up to cut down on memory fragmentation */
	      newsize = (bim->size + 127) & ~(bfd_size_type) 127;
	      if (newsize > oldsize)
	        {
		  bim->buffer = bfd_realloc (bim->buffer, newsize);
		  if (bim->buffer == 0)
		    {
		      bim->size = 0;
		      return -1;
		    }
	        }
	    }
	  else
	    {
	      abfd->where = bim->size;
	      bfd_set_error (bfd_error_file_truncated);
	      return -1;
	    }
	}
      return 0;
    }

  if (abfd->format != bfd_archive && abfd->my_archive == 0)
    {
      if (direction == SEEK_SET && (bfd_vma) position == abfd->where)
	return 0;
    }
  else
    {
      /* We need something smarter to optimize access to archives.
	 Currently, anything inside an archive is read via the file
	 handle for the archive.  Which means that a bfd_seek on one
	 component affects the `current position' in the archive, as
	 well as in any other component.

	 It might be sufficient to put a spike through the cache
	 abstraction, and look to the archive for the file position,
	 but I think we should try for something cleaner.

	 In the meantime, no optimization for archives.  */
    }

  file_position = position;
  if (direction == SEEK_SET && abfd->my_archive != NULL)
    file_position += abfd->origin;

  if (abfd->iovec)
    result = abfd->iovec->bseek (abfd, file_position, direction);
  else
    result = -1;

  if (result != 0)
    {
      int hold_errno = errno;

      /* Force redetermination of `where' field.  */
      bfd_tell (abfd);

      /* An EINVAL error probably means that the file offset was
         absurd.  */
      if (hold_errno == EINVAL)
	bfd_set_error (bfd_error_file_truncated);
      else
	{
	  bfd_set_error (bfd_error_system_call);
	  errno = hold_errno;
	}
    }
  else
    {
      /* Adjust `where' field.  */
      if (direction == SEEK_SET)
	abfd->where = position;
      else
	abfd->where += position;
    }
  return result;
}