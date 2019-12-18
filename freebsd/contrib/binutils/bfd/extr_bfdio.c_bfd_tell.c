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
typedef  scalar_t__ file_ptr ;
struct TYPE_6__ {int flags; scalar_t__ where; scalar_t__ origin; scalar_t__ my_archive; TYPE_1__* iovec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_5__ {scalar_t__ (* btell ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int BFD_IN_MEMORY ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

file_ptr
bfd_tell (bfd *abfd)
{
  file_ptr ptr;

  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    return abfd->where;

  if (abfd->iovec)
    {
      ptr = abfd->iovec->btell (abfd);

      if (abfd->my_archive)
	ptr -= abfd->origin;
    }
  else
    ptr = 0;

  abfd->where = ptr;
  return ptr;
}