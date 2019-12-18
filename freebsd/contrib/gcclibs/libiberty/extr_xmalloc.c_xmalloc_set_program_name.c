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
 char* first_break ; 
 char const* name ; 
 scalar_t__ sbrk (int /*<<< orphan*/ ) ; 

void
xmalloc_set_program_name (const char *s)
{
  name = s;
#ifdef HAVE_SBRK
  /* Win32 ports other than cygwin32 don't have brk() */
  if (first_break == NULL)
    first_break = (char *) sbrk (0);
#endif /* HAVE_SBRK */
}