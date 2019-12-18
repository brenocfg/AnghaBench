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
typedef  scalar_t__ uint16_t ;
struct changer_move {int /*<<< orphan*/  cm_tounit; int /*<<< orphan*/  cm_totype; scalar_t__ cm_fromunit; scalar_t__ cm_fromtype; } ;
struct changer_element_status {int ces_flags; int /*<<< orphan*/  ces_source_addr; int /*<<< orphan*/  ces_source_type; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CES_SOURCE_VALID ; 
 scalar_t__ CHET_VT ; 
 int /*<<< orphan*/  CHIOMOVE ; 
 int /*<<< orphan*/  changer_fd ; 
 int /*<<< orphan*/  changer_name ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  find_element (char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (struct changer_element_status*) ; 
 struct changer_element_status* get_element_status (unsigned int,unsigned int,int) ; 
 char* getprogname () ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct changer_move*) ; 
 int /*<<< orphan*/  memset (struct changer_move*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_element_type (char*) ; 
 scalar_t__ parse_element_unit (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
do_return(const char *cname, int argc, char **argv)
{
	struct changer_element_status *ces;
	struct changer_move cmd;
	uint16_t	type, element;

	++argv; --argc;

	if (argc < 2) {
		warnx("%s: too few arguments", cname);
		goto usage;
	} else if (argc > 3) {
		warnx("%s: too many arguments", cname);
		goto usage;
	}

	type = parse_element_type(*argv);
	++argv; --argc;
	
	/* Handle voltag virtual Changer Element Type */
	if (CHET_VT == type) {
		find_element(*argv, &type, &element);
	} else {
		element = parse_element_unit(*argv);
	}
	++argv; --argc;

	/* Get the status */
	ces = get_element_status((unsigned int)type, (unsigned int)element,
	    CHET_VT == type);

	if (NULL == ces)
		errx(1, "%s: null element status pointer", cname);

	if (!(ces->ces_flags & CES_SOURCE_VALID))
		errx(1, "%s: no source information", cname);

	(void) memset(&cmd, 0, sizeof(cmd));

	cmd.cm_fromtype = type;
	cmd.cm_fromunit = element;
	cmd.cm_totype = ces->ces_source_type;
	cmd.cm_tounit = ces->ces_source_addr;

	if (ioctl(changer_fd, CHIOMOVE, &cmd) == -1)
		err(1, "%s: CHIOMOVE", changer_name);
	free(ces);

	return(0);

usage:
	(void) fprintf(stderr, "usage: %s %s "
	    "<from ET> <from EU>\n", getprogname(), cname);
	return(1);
}