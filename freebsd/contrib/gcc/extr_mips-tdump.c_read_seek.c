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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,long,long) ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 long read (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tfile_fd ; 
 scalar_t__ tfile_offset ; 
 void* xmalloc (size_t) ; 

__attribute__((used)) static void *
read_seek (void *ptr, size_t size, off_t offset,  const char *context)
{
  long read_size = 0;

  if (size == 0)		/* nothing to read */
    return ptr;

  if (!ptr)
    ptr = xmalloc (size);

  if ((tfile_offset != offset && lseek (tfile_fd, offset, 0) == -1)
      || (read_size = read (tfile_fd, ptr, size)) < 0)
    {
      perror (context);
      exit (1);
    }

  if (read_size != (long) size)
    {
      fprintf (stderr, "%s: read %ld bytes, expected %ld bytes\n",
	       context, read_size, (long) size);
      exit (1);
    }

  tfile_offset = offset + size;
  return ptr;
}