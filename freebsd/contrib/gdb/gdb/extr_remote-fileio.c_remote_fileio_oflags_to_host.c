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

/* Variables and functions */
 long FILEIO_O_APPEND ; 
 long FILEIO_O_CREAT ; 
 long FILEIO_O_EXCL ; 
 long FILEIO_O_RDONLY ; 
 long FILEIO_O_RDWR ; 
 long FILEIO_O_TRUNC ; 
 long FILEIO_O_WRONLY ; 
 int O_APPEND ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 

__attribute__((used)) static int
remote_fileio_oflags_to_host (long flags)
{
  int hflags = 0;

  if (flags & FILEIO_O_CREAT)
    hflags |= O_CREAT;
  if (flags & FILEIO_O_EXCL)
    hflags |= O_EXCL;
  if (flags & FILEIO_O_TRUNC)
    hflags |= O_TRUNC;
  if (flags & FILEIO_O_APPEND)
    hflags |= O_APPEND;
  if (flags & FILEIO_O_RDONLY)
    hflags |= O_RDONLY;
  if (flags & FILEIO_O_WRONLY)
    hflags |= O_WRONLY;
  if (flags & FILEIO_O_RDWR)
    hflags |= O_RDWR;
/* On systems supporting binary and text mode, always open files in
   binary mode. */
#ifdef O_BINARY
  hflags |= O_BINARY;
#endif
  return hflags;
}