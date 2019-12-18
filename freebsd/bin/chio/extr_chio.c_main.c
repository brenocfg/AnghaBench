#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * cc_name; int /*<<< orphan*/  (* cc_handler ) (int /*<<< orphan*/ *,int,char**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGER_ENV_VAR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/ * _PATH_CH ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int changer_fd ; 
 int /*<<< orphan*/ * changer_name ; 
 int /*<<< orphan*/  cleanup ; 
 TYPE_1__* commands ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * optarg ; 
 scalar_t__ optind ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ch, i;

	while ((ch = getopt(argc, argv, "f:")) != -1) {
		switch (ch) {
		case 'f':
			changer_name = optarg;
			break;

		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	/* Get the default changer if not already specified. */
	if (changer_name == NULL)
		if ((changer_name = getenv(CHANGER_ENV_VAR)) == NULL)
			changer_name = _PATH_CH;

	/* Open the changer device. */
	if ((changer_fd = open(changer_name, O_RDWR, 0600)) == -1)
		err(1, "%s: open", changer_name);

	/* Register cleanup function. */
	if (atexit(cleanup))
		err(1, "can't register cleanup function");

	/* Find the specified command. */
	for (i = 0; commands[i].cc_name != NULL; ++i)
		if (strcmp(*argv, commands[i].cc_name) == 0)
			break;
	if (commands[i].cc_name == NULL) {
		/* look for abbreviation */
		for (i = 0; commands[i].cc_name != NULL; ++i)
			if (strncmp(*argv, commands[i].cc_name,
			    strlen(*argv)) == 0)
				break;
	}

	if (commands[i].cc_name == NULL)
		errx(1, "unknown command: %s", *argv);

	exit ((*commands[i].cc_handler)(commands[i].cc_name, argc, argv));
	/* NOTREACHED */
}