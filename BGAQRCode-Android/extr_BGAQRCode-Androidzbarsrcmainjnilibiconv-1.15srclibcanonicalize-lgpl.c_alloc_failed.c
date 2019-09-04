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

__attribute__((used)) static void
alloc_failed (void)
{
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
  /* Avoid errno problem without using the malloc or realloc modules; see:
     http://lists.gnu.org/archive/html/bug-gnulib/2016-08/msg00025.html  */
  errno = ENOMEM;
#endif
}