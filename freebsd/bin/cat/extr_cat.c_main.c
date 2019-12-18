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
struct flock {int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; scalar_t__ l_start; scalar_t__ l_len; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int bflag ; 
 void* eflag ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int getopt (int,char**,char*) ; 
 int lflag ; 
 int nflag ; 
 int /*<<< orphan*/  optind ; 
 int /*<<< orphan*/  rval ; 
 int /*<<< orphan*/  scanfiles (char**,int) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int sflag ; 
 int /*<<< orphan*/  stdout ; 
 void* tflag ; 
 int /*<<< orphan*/  usage () ; 
 void* vflag ; 

int
main(int argc, char *argv[])
{
	int ch;
	struct flock stdout_lock;

	setlocale(LC_CTYPE, "");

	while ((ch = getopt(argc, argv, "belnstuv")) != -1)
		switch (ch) {
		case 'b':
			bflag = nflag = 1;	/* -b implies -n */
			break;
		case 'e':
			eflag = vflag = 1;	/* -e implies -v */
			break;
		case 'l':
			lflag = 1;
			break;
		case 'n':
			nflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 't':
			tflag = vflag = 1;	/* -t implies -v */
			break;
		case 'u':
			setbuf(stdout, NULL);
			break;
		case 'v':
			vflag = 1;
			break;
		default:
			usage();
		}
	argv += optind;

	if (lflag) {
		stdout_lock.l_len = 0;
		stdout_lock.l_start = 0;
		stdout_lock.l_type = F_WRLCK;
		stdout_lock.l_whence = SEEK_SET;
		if (fcntl(STDOUT_FILENO, F_SETLKW, &stdout_lock) == -1)
			err(EXIT_FAILURE, "stdout");
	}

	if (bflag || eflag || nflag || sflag || tflag || vflag)
		scanfiles(argv, 1);
	else
		scanfiles(argv, 0);
	if (fclose(stdout))
		err(1, "stdout");
	exit(rval);
	/* NOTREACHED */
}