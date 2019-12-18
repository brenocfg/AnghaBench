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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ccl_contains (int,int) ; 
 int csize ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 char* readable_form (int) ; 

__attribute__((used)) static void    dump_cclp (FILE* file, int cclp)
{
	int i;

	putc ('[', file);

	for (i = 0; i < csize; ++i) {
		if (ccl_contains(cclp, i)){
			int start_char = i;

			putc (' ', file);

			fputs (readable_form (i), file);

			while (++i < csize && ccl_contains(cclp,i)) ;

			if (i - 1 > start_char)
				/* this was a run */
				fprintf (file, "-%s",
					 readable_form (i - 1));

			putc (' ', file);
		}
	}

	putc (']', file);
}