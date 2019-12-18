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
struct changer_move {scalar_t__ cm_fromtype; scalar_t__ cm_totype; int /*<<< orphan*/  cm_flags; void* cm_tounit; void* cm_fromunit; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 scalar_t__ CHET_VT ; 
 int /*<<< orphan*/  CHIOMOVE ; 
 int /*<<< orphan*/  CM_INVERT ; 
#define  SW_INVERT 128 
 int /*<<< orphan*/  changer_fd ; 
 int /*<<< orphan*/  changer_name ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 int /*<<< orphan*/  find_element (char*,scalar_t__*,void**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* getprogname () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct changer_move*) ; 
 int /*<<< orphan*/  memset (struct changer_move*,int /*<<< orphan*/ ,int) ; 
 void* parse_element_type (char*) ; 
 void* parse_element_unit (char*) ; 
 int parse_special (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
do_move(const char *cname, int argc, char **argv)
{
	struct changer_move cmd;
	int val;

	/*
	 * On a move command, we expect the following:
	 *
	 * <from ET> <from EU> <to ET> <to EU> [inv]
	 *
	 * where ET == element type and EU == element unit.
	 */

	++argv; --argc;

	if (argc < 4) {
		warnx("%s: too few arguments", cname);
		goto usage;
	} else if (argc > 5) {
		warnx("%s: too many arguments", cname);
		goto usage;
	}
	(void) memset(&cmd, 0, sizeof(cmd));

	/* <from ET>  */
	cmd.cm_fromtype = parse_element_type(*argv);
	++argv; --argc;

	/* Check for voltag virtual type */
	if (CHET_VT == cmd.cm_fromtype) {
		find_element(*argv, &cmd.cm_fromtype, &cmd.cm_fromunit);
	} else {
		/* <from EU> */
		cmd.cm_fromunit = parse_element_unit(*argv);
	}
	++argv; --argc;

	/* <to ET> */
	cmd.cm_totype = parse_element_type(*argv);
	++argv; --argc;

	/* Check for voltag virtual type, and report error */
	if (CHET_VT == cmd.cm_totype)
		errx(1,"%s: voltag only makes sense as an element source",
		     cname);

	/* <to EU> */
	cmd.cm_tounit = parse_element_unit(*argv);
	++argv; --argc;

	/* Deal with optional command modifier. */
	if (argc) {
		val = parse_special(*argv);
		switch (val) {
		case SW_INVERT:
			cmd.cm_flags |= CM_INVERT;
			break;

		default:
			errx(1, "%s: inappropriate modifier `%s'",
			    cname, *argv);
			/* NOTREACHED */
		}
	}

	/* Send command to changer. */
	if (ioctl(changer_fd, CHIOMOVE, &cmd))
		err(1, "%s: CHIOMOVE", changer_name);

	return (0);

 usage:
	(void) fprintf(stderr, "usage: %s %s "
	    "<from ET> <from EU> <to ET> <to EU> [inv]\n", getprogname(), cname);
	return (1);
}