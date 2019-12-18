#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ off_t ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int ftruncate (int,size_t) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 

__attribute__((used)) static void *
cygwin_gt_pch_get_address (size_t sz, int fd)
{
  void *base;
  off_t p = lseek(fd, 0, SEEK_CUR);

  if (p == (off_t) -1)
    fatal_error ("can't get position in PCH file: %m");

   /* Cygwin requires that the underlying file be at least
      as large as the requested mapping.  */
  if ((size_t) p < sz)
  { 
    if ( ftruncate (fd, sz) == -1 )
      fatal_error ("can't extend PCH file: %m");
  }

  base = mmap (NULL, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

  if (base == MAP_FAILED)
    base = NULL;
  else
    munmap (base, sz);

  if (lseek (fd, p, SEEK_SET) == (off_t) -1 )
    fatal_error ("can't set position in PCH file: %m");

  return base;
}