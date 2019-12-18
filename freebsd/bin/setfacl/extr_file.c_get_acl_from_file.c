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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  acl_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  acl_from_text (char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int have_stdin ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 

acl_t
get_acl_from_file(const char *filename)
{
	FILE *file;
	size_t len;
	char buf[BUFSIZ+1];

	if (filename == NULL)
		err(1, "(null) filename in get_acl_from_file()");

	if (strcmp(filename, "-") == 0) {
		if (have_stdin)
			err(1, "cannot specify more than one stdin");
		file = stdin;
		have_stdin = true;
	} else {
		file = fopen(filename, "r");
		if (file == NULL)
			err(1, "fopen() %s failed", filename);
	}

	len = fread(buf, (size_t)1, sizeof(buf) - 1, file);
	buf[len] = '\0';
	if (ferror(file) != 0) {
		fclose(file);
		err(1, "error reading from %s", filename);
	} else if (feof(file) == 0) {
		fclose(file);
		errx(1, "line too long in %s", filename);
	}

	fclose(file);

	return (acl_from_text(buf));
}