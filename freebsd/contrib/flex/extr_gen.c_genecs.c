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
 int ABS (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int csize ; 
 int /*<<< orphan*/  dataend () ; 
 int* ecgroup ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_int32_decl () ; 
 int /*<<< orphan*/  mkdata (int) ; 
 int /*<<< orphan*/  out_str_dec (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 char* readable_form (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ trace ; 

void genecs ()
{
	int i, j;
	int     numrows;

	out_str_dec (get_int32_decl (), "yy_ec", csize);

	for (i = 1; i < csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		mkdata (ecgroup[i]);
	}

	dataend ();

	if (trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		numrows = csize / 8;

		for (j = 0; j < numrows; ++j) {
			for (i = j; i < csize; i = i + numrows) {
				fprintf (stderr, "%4s = %-2d",
					 readable_form (i), ecgroup[i]);

				putc (' ', stderr);
			}

			putc ('\n', stderr);
		}
	}
}