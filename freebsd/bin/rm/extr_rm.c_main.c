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
 int Iflag ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  SIGINFO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int Wflag ; 
 scalar_t__ check2 (char**) ; 
 int /*<<< orphan*/  checkdot (char**) ; 
 int /*<<< orphan*/  checkslash (char**) ; 
 int dflag ; 
 int eval ; 
 int /*<<< orphan*/  exit (int) ; 
 int fflag ; 
 int /*<<< orphan*/  geteuid () ; 
 int getopt (int,char**,char*) ; 
 int iflag ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int rflag ; 
 int /*<<< orphan*/  rm_file (char**) ; 
 int /*<<< orphan*/  rm_tree (char**) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  siginfo ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin_ok ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  uid ; 
 int /*<<< orphan*/  usage () ; 
 int vflag ; 
 int xflag ; 

int
main(int argc, char *argv[])
{
	int ch;
	char *p;

	(void)setlocale(LC_ALL, "");

	/*
	 * Test for the special case where the utility is called as
	 * "unlink", for which the functionality provided is greatly
	 * simplified.
	 */
	if ((p = strrchr(argv[0], '/')) == NULL)
		p = argv[0];
	else
		++p;
	if (strcmp(p, "unlink") == 0) {
		if (argc == 2)
			rm_file(&argv[1]);
		else if (argc == 3 && strcmp(argv[1], "--") == 0)
			rm_file(&argv[2]);
		else
			usage();
		exit(eval);
	}

	rflag = xflag = 0;
	while ((ch = getopt(argc, argv, "dfiIPRrvWx")) != -1)
		switch(ch) {
		case 'd':
			dflag = 1;
			break;
		case 'f':
			fflag = 1;
			iflag = 0;
			break;
		case 'i':
			fflag = 0;
			iflag = 1;
			break;
		case 'I':
			Iflag = 1;
			break;
		case 'P':
			/* Compatibility no-op. */
			break;
		case 'R':
		case 'r':			/* Compatibility. */
			rflag = 1;
			break;
		case 'v':
			vflag = 1;
			break;
		case 'W':
			Wflag = 1;
			break;
		case 'x':
			xflag = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc < 1) {
		if (fflag)
			return (0);
		usage();
	}

	checkdot(argv);
	checkslash(argv);
	uid = geteuid();

	(void)signal(SIGINFO, siginfo);
	if (*argv) {
		stdin_ok = isatty(STDIN_FILENO);

		if (Iflag) {
			if (check2(argv) == 0)
				exit (1);
		}
		if (rflag)
			rm_tree(argv);
		else
			rm_file(argv);
	}

	exit (eval);
}