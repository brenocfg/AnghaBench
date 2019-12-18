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
struct stat {int /*<<< orphan*/  st_size; } ;
struct bfd_in_memory {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  file_ptr ;
struct TYPE_6__ {int flags; TYPE_1__* iovec; scalar_t__ iostream; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_5__ {scalar_t__ (* bstat ) (TYPE_2__*,struct stat*) ;} ;

/* Variables and functions */
 int BFD_IN_MEMORY ; 
 scalar_t__ stub1 (TYPE_2__*,struct stat*) ; 

file_ptr
bfd_get_size (bfd *abfd)
{
  struct stat buf;

  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    return ((struct bfd_in_memory *) abfd->iostream)->size;

  if (abfd->iovec == NULL)
    return 0;

  if (abfd->iovec->bstat (abfd, &buf) != 0)
    return 0;

  return buf.st_size;
}