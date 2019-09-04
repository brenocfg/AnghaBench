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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  readlink (char const*,char*,size_t) ; 

__attribute__((used)) static ssize_t
careadlinkatcwd (int fd, char const *filename, char *buffer,
                 size_t buffer_size)
{
  /* FD must be AT_FDCWD here, otherwise the caller is using this
     function in contexts it was not meant for.  */
  if (fd != AT_FDCWD)
    abort ();
  return readlink (filename, buffer, buffer_size);
}