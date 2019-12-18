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
 int PATH_MAX ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* realpath (char const*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

int
main(int argc, char *argv[])
{
	char buf[PATH_MAX];
	char *p;
	const char *path;
	int ch, qflag, rval;

	qflag = 0;
	while ((ch = getopt(argc, argv, "q")) != -1) {
		switch (ch) {
		case 'q':
			qflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	path = *argv != NULL ? *argv++ : ".";
	rval  = 0;
	do {
		if ((p = realpath(path, buf)) == NULL) {
			if (!qflag)
				warn("%s", path);
			rval = 1;
		} else
			(void)printf("%s\n", p);
	} while ((path = *argv++) != NULL);
	exit(rval);
}