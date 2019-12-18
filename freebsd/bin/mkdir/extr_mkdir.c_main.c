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
typedef  int mode_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int build (char*,int) ; 
 int chmod (char*,int) ; 
 char* dirname (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int getmode (void*,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 void* setmode (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int vflag ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	int ch, exitval, success, pflag;
	mode_t omode;
	void *set = NULL;
	char *mode;

	omode = pflag = 0;
	mode = NULL;
	while ((ch = getopt(argc, argv, "m:pv")) != -1)
		switch(ch) {
		case 'm':
			mode = optarg;
			break;
		case 'p':
			pflag = 1;
			break;
		case 'v':
			vflag = 1;
			break;
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;
	if (argv[0] == NULL)
		usage();

	if (mode == NULL) {
		omode = S_IRWXU | S_IRWXG | S_IRWXO;
	} else {
		if ((set = setmode(mode)) == NULL)
			errx(1, "invalid file mode: %s", mode);
		omode = getmode(set, S_IRWXU | S_IRWXG | S_IRWXO);
		free(set);
	}

	for (exitval = 0; *argv != NULL; ++argv) {
		if (pflag) {
			success = build(*argv, omode);
		} else if (mkdir(*argv, omode) < 0) {
			if (errno == ENOTDIR || errno == ENOENT)
				warn("%s", dirname(*argv));
			else
				warn("%s", *argv);
			success = 0;
		} else {
			success = 1;
			if (vflag)
				(void)printf("%s\n", *argv);
		}
		if (!success)
			exitval = 1;
		/*
		 * The mkdir() and umask() calls both honor only the low
		 * nine bits, so if you try to set a mode including the
		 * sticky, setuid, setgid bits you lose them.  Don't do
		 * this unless the user has specifically requested a mode,
		 * as chmod will (obviously) ignore the umask.  Do this
		 * on newly created directories only.
		 */
		if (success == 1 && mode != NULL && chmod(*argv, omode) == -1) {
			warn("%s", *argv);
			exitval = 1;
		}
	}
	exit(exitval);
}