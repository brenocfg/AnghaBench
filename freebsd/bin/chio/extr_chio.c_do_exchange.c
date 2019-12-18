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
struct changer_exchange {scalar_t__ ce_srctype; scalar_t__ ce_fdsttype; scalar_t__ ce_sdsttype; int /*<<< orphan*/  ce_flags; void* ce_sdstunit; void* ce_srcunit; void* ce_fdstunit; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CE_INVERT1 ; 
 int /*<<< orphan*/  CE_INVERT2 ; 
 scalar_t__ CHET_VT ; 
 int /*<<< orphan*/  CHIOEXCHANGE ; 
#define  SW_INVERT1 129 
#define  SW_INVERT2 128 
 int /*<<< orphan*/  changer_fd ; 
 int /*<<< orphan*/  changer_name ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char*) ; 
 int /*<<< orphan*/  find_element (char*,scalar_t__*,void**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* getprogname () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct changer_exchange*) ; 
 scalar_t__ is_special (char*) ; 
 int /*<<< orphan*/  memset (struct changer_exchange*,int /*<<< orphan*/ ,int) ; 
 void* parse_element_type (char*) ; 
 void* parse_element_unit (char*) ; 
 int parse_special (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
do_exchange(const char *cname, int argc, char **argv)
{
	struct changer_exchange cmd;
	int val;

	/*
	 * On an exchange command, we expect the following:
	 *
  * <src ET> <src EU> <dst1 ET> <dst1 EU> [<dst2 ET> <dst2 EU>] [inv1] [inv2]
	 *
	 * where ET == element type and EU == element unit.
	 */

	++argv; --argc;

	if (argc < 4) {
		warnx("%s: too few arguments", cname);
		goto usage;
	} else if (argc > 8) {
		warnx("%s: too many arguments", cname);
		goto usage;
	}
	(void) memset(&cmd, 0, sizeof(cmd));

	/* <src ET>  */
	cmd.ce_srctype = parse_element_type(*argv);
	++argv; --argc;

	/* Check for voltag virtual type */
	if (CHET_VT == cmd.ce_srctype) {
		find_element(*argv, &cmd.ce_srctype, &cmd.ce_srcunit);
	} else {
		/* <from EU> */
		cmd.ce_srcunit = parse_element_unit(*argv);
	}
	++argv; --argc;

	/* <dst1 ET> */
	cmd.ce_fdsttype = parse_element_type(*argv);
	++argv; --argc;

	/* Check for voltag virtual type */
	if (CHET_VT == cmd.ce_fdsttype) {
		find_element(*argv, &cmd.ce_fdsttype, &cmd.ce_fdstunit);
	} else {
		/* <from EU> */
		cmd.ce_fdstunit = parse_element_unit(*argv);
	}
	++argv; --argc;

	/*
	 * If the next token is a special word or there are no more
	 * arguments, then this is a case of simple exchange.
	 * dst2 == src.
	 */
	if ((argc == 0) || is_special(*argv)) {
		cmd.ce_sdsttype = cmd.ce_srctype;
		cmd.ce_sdstunit = cmd.ce_srcunit;
		goto do_special;
	}

	/* <dst2 ET> */
	cmd.ce_sdsttype = parse_element_type(*argv);
	++argv; --argc;

	if (CHET_VT == cmd.ce_sdsttype)
		errx(1,"%s %s: voltag only makes sense as an element source",
		     cname, *argv);

	/* <dst2 EU> */
	cmd.ce_sdstunit = parse_element_unit(*argv);
	++argv; --argc;

 do_special:
	/* Deal with optional command modifiers. */
	while (argc) {
		val = parse_special(*argv);
		++argv; --argc;
		switch (val) {
		case SW_INVERT1:
			cmd.ce_flags |= CE_INVERT1;
			break;

		case SW_INVERT2:
			cmd.ce_flags |= CE_INVERT2;
			break;

		default:
			errx(1, "%s: inappropriate modifier `%s'",
			    cname, *argv);
			/* NOTREACHED */
		}
	}

	/* Send command to changer. */
	if (ioctl(changer_fd, CHIOEXCHANGE, &cmd))
		err(1, "%s: CHIOEXCHANGE", changer_name);

	return (0);

 usage:
	(void) fprintf(stderr,
	    "usage: %s %s <src ET> <src EU> <dst1 ET> <dst1 EU>\n"
	    "       [<dst2 ET> <dst2 EU>] [inv1] [inv2]\n",
	    getprogname(), cname);
	return (1);
}