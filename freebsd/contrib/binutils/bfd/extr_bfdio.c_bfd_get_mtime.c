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
struct stat {long st_mtime; } ;
struct TYPE_6__ {long mtime; TYPE_1__* iovec; scalar_t__ mtime_set; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_5__ {scalar_t__ (* bstat ) (TYPE_2__*,struct stat*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_2__*,struct stat*) ; 

long
bfd_get_mtime (bfd *abfd)
{
  struct stat buf;

  if (abfd->mtime_set)
    return abfd->mtime;

  if (abfd->iovec == NULL)
    return 0;

  if (abfd->iovec->bstat (abfd, &buf) != 0)
    return 0;

  abfd->mtime = buf.st_mtime;		/* Save value in case anyone wants it */
  return buf.st_mtime;
}