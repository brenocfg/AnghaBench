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
struct changer_position {int /*<<< orphan*/  cp_flags; int /*<<< orphan*/  cp_unit; int /*<<< orphan*/  cp_type; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CHIOPOSITION ; 
 int /*<<< orphan*/  CP_INVERT ; 
#define  SW_INVERT 128 
 int /*<<< orphan*/  changer_fd ; 
 int /*<<< orphan*/  changer_name ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* getprogname () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct changer_position*) ; 
 int /*<<< orphan*/  memset (struct changer_position*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_element_type (char*) ; 
 int /*<<< orphan*/  parse_element_unit (char*) ; 
 int parse_special (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
do_position(const char *cname, int argc, char **argv)
{
	struct changer_position cmd;
	int val;

	/*
	 * On a position command, we expect the following:
	 *
	 * <to ET> <to EU> [inv]
	 *
	 * where ET == element type and EU == element unit.
	 */

	++argv; --argc;

	if (argc < 2) {
		warnx("%s: too few arguments", cname);
		goto usage;
	} else if (argc > 3) {
		warnx("%s: too many arguments", cname);
		goto usage;
	}
	(void) memset(&cmd, 0, sizeof(cmd));

	/* <to ET>  */
	cmd.cp_type = parse_element_type(*argv);
	++argv; --argc;

	/* <to EU> */
	cmd.cp_unit = parse_element_unit(*argv);
	++argv; --argc;

	/* Deal with optional command modifier. */
	if (argc) {
		val = parse_special(*argv);
		switch (val) {
		case SW_INVERT:
			cmd.cp_flags |= CP_INVERT;
			break;

		default:
			errx(1, "%s: inappropriate modifier `%s'",
			    cname, *argv);
			/* NOTREACHED */
		}
	}

	/* Send command to changer. */
	if (ioctl(changer_fd, CHIOPOSITION, &cmd))
		err(1, "%s: CHIOPOSITION", changer_name);

	return (0);

 usage:
	(void) fprintf(stderr, "usage: %s %s <to ET> <to EU> [inv]\n",
	    getprogname(), cname);
	return (1);
}