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
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int,void*,int) ; 

__attribute__((used)) static int
safe_read (int desc, void *ptr, int len)
{
  int left = len;
  while (left > 0) {
    int nchars = read (desc, ptr, left);
    if (nchars < 0)
      {
#ifdef EINTR
	if (errno == EINTR)
	  continue;
#endif
	return nchars;
      }
    if (nchars == 0)
      break;
    /* Arithmetic on void pointers is a gcc extension.  */
    ptr = (char *) ptr + nchars;
    left -= nchars;
  }
  return len - left;
}