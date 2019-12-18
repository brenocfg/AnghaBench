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
 int /*<<< orphan*/  CHIOGPICKER ; 
 int /*<<< orphan*/  changer_fd ; 
 char* changer_name ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* getprogname () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
do_getpicker(const char *cname, int argc, char **argv)
{
	int picker;

	/* No arguments to this command. */

	++argv; --argc;

	if (argc) {
		warnx("%s: no arguments expected", cname);
		goto usage;
	}

	/* Get current picker from changer and display it. */
	if (ioctl(changer_fd, CHIOGPICKER, &picker))
		err(1, "%s: CHIOGPICKER", changer_name);

	(void) printf("%s: current picker: %d\n", changer_name, picker);

	return (0);

 usage:
	(void) fprintf(stderr, "usage: %s %s\n", getprogname(), cname);
	return (1);
}