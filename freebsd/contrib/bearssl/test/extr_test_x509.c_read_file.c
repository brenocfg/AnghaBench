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
 char* DIRNAME ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 unsigned char* read_all (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static unsigned char *
read_file(const char *name, size_t *len)
{
	FILE *f;
	unsigned char *buf;

#ifdef DIRNAME
	char *dname;

	dname = xmalloc(strlen(DIRNAME) + strlen(name) + 2);
	sprintf(dname, "%s/%s", DIRNAME, name);
	name = dname;
#endif
	f = fopen(name, "rb");
	if (f == NULL) {
		fprintf(stderr, "could not open file '%s'\n", name);
		exit(EXIT_FAILURE);
	}
	buf = read_all(f, len);
	if (ferror(f)) {
		fprintf(stderr, "read error on file '%s'\n", name);
		exit(EXIT_FAILURE);
	}
	fclose(f);
#ifdef DIRNAME
	xfree(dname);
#endif
	return buf;
}