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
struct info {int set; int wset; int /*<<< orphan*/  win; int /*<<< orphan*/  fd; int /*<<< orphan*/  t; int /*<<< orphan*/  ldisc; } ;
typedef  int /*<<< orphan*/  speed_t ;
typedef  enum FMT { ____Placeholder_FMT } FMT ;

/* Variables and functions */
#define  BSD 131 
#define  GFLAG 130 
#define  NOTSET 129 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
#define  POSIX 128 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TIOCGETD ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  cfsetispeed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkredirect () ; 
 scalar_t__ csearch (char***,struct info*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  gprint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gread (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ ksearch (char***,struct info*) ; 
 scalar_t__ msearch (char***,struct info*) ; 
 int /*<<< orphan*/  open (char*,int) ; 
 char* optarg ; 
 scalar_t__ opterr ; 
 int optind ; 
 int /*<<< orphan*/  print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 scalar_t__ strspn (char*,char*) ; 
 int /*<<< orphan*/  strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char *argv[])
{
	struct info i;
	enum FMT fmt;
	int ch;
	const char *file, *errstr = NULL;

	fmt = NOTSET;
	i.fd = STDIN_FILENO;
	file = "stdin";

	opterr = 0;
	while (optind < argc &&
	    strspn(argv[optind], "-aefg") == strlen(argv[optind]) &&
	    (ch = getopt(argc, argv, "aef:g")) != -1)
		switch(ch) {
		case 'a':		/* undocumented: POSIX compatibility */
			fmt = POSIX;
			break;
		case 'e':
			fmt = BSD;
			break;
		case 'f':
			if ((i.fd = open(optarg, O_RDONLY | O_NONBLOCK)) < 0)
				err(1, "%s", optarg);
			file = optarg;
			break;
		case 'g':
			fmt = GFLAG;
			break;
		case '?':
		default:
			goto args;
		}

args:	argc -= optind;
	argv += optind;

	if (tcgetattr(i.fd, &i.t) < 0)
		errx(1, "%s isn't a terminal", file);
	if (ioctl(i.fd, TIOCGETD, &i.ldisc) < 0)
		err(1, "TIOCGETD");
	if (ioctl(i.fd, TIOCGWINSZ, &i.win) < 0)
		warn("TIOCGWINSZ");

	checkredirect();			/* conversion aid */

	switch(fmt) {
	case NOTSET:
		if (*argv)
			break;
		/* FALLTHROUGH */
	case BSD:
	case POSIX:
		print(&i.t, &i.win, i.ldisc, fmt);
		break;
	case GFLAG:
		gprint(&i.t, &i.win, i.ldisc);
		break;
	}

	for (i.set = i.wset = 0; *argv; ++argv) {
		if (ksearch(&argv, &i))
			continue;

		if (csearch(&argv, &i))
			continue;

		if (msearch(&argv, &i))
			continue;

		if (isdigit(**argv)) {
			speed_t speed;

			speed = strtonum(*argv, 0, UINT_MAX, &errstr);
			if (errstr)
				err(1, "speed");
			cfsetospeed(&i.t, speed);
			cfsetispeed(&i.t, speed);
			i.set = 1;
			continue;
		}

		if (!strncmp(*argv, "gfmt1", sizeof("gfmt1") - 1)) {
			gread(&i.t, *argv + sizeof("gfmt1") - 1);
			i.set = 1;
			continue;
		}

		warnx("illegal option -- %s", *argv);
		usage();
	}

	if (i.set && tcsetattr(i.fd, 0, &i.t) < 0)
		err(1, "tcsetattr");
	if (i.wset && ioctl(i.fd, TIOCSWINSZ, &i.win) < 0)
		warn("TIOCSWINSZ");
	exit(0);
}