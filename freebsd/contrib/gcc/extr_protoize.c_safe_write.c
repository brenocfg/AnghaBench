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
 int EINTR ; 
 int errno ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pname ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,char const*) ; 
 int write (int,void*,int) ; 
 int /*<<< orphan*/  xstrerror (int) ; 

__attribute__((used)) static void
safe_write (int desc, void *ptr, int len, const char *out_fname)
{
  while (len > 0) {
    int written = write (desc, ptr, len);
    if (written < 0)
      {
	int errno_val = errno;
#ifdef EINTR
	if (errno_val == EINTR)
	  continue;
#endif
	notice ("%s: error writing file '%s': %s\n",
		pname, shortpath (NULL, out_fname), xstrerror (errno_val));
	return;
      }
    /* Arithmetic on void pointers is a gcc extension.  */
    ptr = (char *) ptr + written;
    len -= written;
  }
}