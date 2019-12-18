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
 int /*<<< orphan*/  CHIOIELEM ; 
 int atol (char*) ; 
 int /*<<< orphan*/  changer_fd ; 
 int /*<<< orphan*/  changer_name ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* getprogname () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
do_ielem(const char *cname, int argc, char **argv)
{
	int timeout = 0;

	if (argc == 2) {
		timeout = atol(argv[1]);
	} else if (argc > 1) {
		warnx("%s: too many arguments", cname);
		goto usage;
	}

	if (ioctl(changer_fd, CHIOIELEM, &timeout))
		err(1, "%s: CHIOIELEM", changer_name);

	return (0);

 usage:
	(void) fprintf(stderr, "usage: %s %s [<timeout>]\n",
		       getprogname(), cname);
	return (1);
}