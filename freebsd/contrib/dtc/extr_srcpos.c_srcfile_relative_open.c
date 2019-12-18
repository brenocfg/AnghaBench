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
 scalar_t__ depfile ; 
 int /*<<< orphan*/  die (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* fopen_any_on_path (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* xstrdup (char*) ; 

FILE *srcfile_relative_open(const char *fname, char **fullnamep)
{
	FILE *f;
	char *fullname;

	if (streq(fname, "-")) {
		f = stdin;
		fullname = xstrdup("<stdin>");
	} else {
		fullname = fopen_any_on_path(fname, &f);
		if (!f)
			die("Couldn't open \"%s\": %s\n", fname,
			    strerror(errno));
	}

	if (depfile)
		fprintf(depfile, " %s", fullname);

	if (fullnamep)
		*fullnamep = fullname;
	else
		free(fullname);

	return f;
}