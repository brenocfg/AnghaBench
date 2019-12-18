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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,unsigned long,...) ; 
 char* name ; 
 scalar_t__ sbrk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xexit (int) ; 

void
xmalloc_failed (size_t size)
{
#ifdef HAVE_SBRK
  extern char **environ;
  size_t allocated;

  if (first_break != NULL)
    allocated = (char *) sbrk (0) - first_break;
  else
    allocated = (char *) sbrk (0) - (char *) &environ;
  fprintf (stderr,
	   "\n%s%sout of memory allocating %lu bytes after a total of %lu bytes\n",
	   name, *name ? ": " : "",
	   (unsigned long) size, (unsigned long) allocated);
#else /* HAVE_SBRK */
  fprintf (stderr,
	   "\n%s%sout of memory allocating %lu bytes\n",
	   name, *name ? ": " : "",
	   (unsigned long) size);
#endif /* HAVE_SBRK */
  xexit (1);
}