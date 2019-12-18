#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {unsigned int st_mode; } ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_5__ {scalar_t__ direction; int flags; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int EXEC_P ; 
 unsigned int S_IXGRP ; 
 unsigned int S_IXOTH ; 
 unsigned int S_IXUSR ; 
 int /*<<< orphan*/  _bfd_delete_bfd (TYPE_1__*) ; 
 scalar_t__ bfd_cache_close (TYPE_1__*) ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 unsigned int umask (unsigned int) ; 
 scalar_t__ write_direction ; 

bfd_boolean
bfd_close_all_done (bfd *abfd)
{
  bfd_boolean ret;

  ret = bfd_cache_close (abfd);

  /* If the file was open for writing and is now executable,
     make it so.  */
  if (ret
      && abfd->direction == write_direction
      && abfd->flags & EXEC_P)
    {
      struct stat buf;

      if (stat (abfd->filename, &buf) == 0)
	{
	  unsigned int mask = umask (0);

	  umask (mask);
	  chmod (abfd->filename,
		 (0777
		  & (buf.st_mode | ((S_IXUSR | S_IXGRP | S_IXOTH) &~ mask))));
	}
    }

  _bfd_delete_bfd (abfd);

  return ret;
}