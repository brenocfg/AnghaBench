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
struct bfd_in_memory {int size; scalar_t__ buffer; } ;
typedef  int bfd_size_type ;
struct TYPE_6__ {int flags; int where; TYPE_1__* iovec; struct bfd_in_memory* iostream; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_5__ {size_t (* bwrite ) (TYPE_2__*,void const*,int) ;} ;

/* Variables and functions */
 int BFD_IN_MEMORY ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 scalar_t__ bfd_realloc (scalar_t__,int) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 size_t stub1 (TYPE_2__*,void const*,int) ; 

bfd_size_type
bfd_bwrite (const void *ptr, bfd_size_type size, bfd *abfd)
{
  size_t nwrote;

  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    {
      struct bfd_in_memory *bim = abfd->iostream;

      size = (size_t) size;
      if (abfd->where + size > bim->size)
	{
	  bfd_size_type newsize, oldsize;

	  oldsize = (bim->size + 127) & ~(bfd_size_type) 127;
	  bim->size = abfd->where + size;
	  /* Round up to cut down on memory fragmentation */
	  newsize = (bim->size + 127) & ~(bfd_size_type) 127;
	  if (newsize > oldsize)
	    {
	      bim->buffer = bfd_realloc (bim->buffer, newsize);
	      if (bim->buffer == 0)
		{
		  bim->size = 0;
		  return 0;
		}
	    }
	}
      memcpy (bim->buffer + abfd->where, ptr, (size_t) size);
      abfd->where += size;
      return size;
    }

  if (abfd->iovec)
    nwrote = abfd->iovec->bwrite (abfd, ptr, size);
  else
    nwrote = 0;

  if (nwrote != (size_t) -1)
    abfd->where += nwrote;
  if (nwrote != size)
    {
#ifdef ENOSPC
      errno = ENOSPC;
#endif
      bfd_set_error (bfd_error_system_call);
    }
  return nwrote;
}