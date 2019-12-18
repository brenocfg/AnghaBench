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
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ gethostname (char*,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ sethostname (char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, sflag, dflag;
	char *p, hostname[MAXHOSTNAMELEN];

	sflag = 0;
	dflag = 0;
	while ((ch = getopt(argc, argv, "fsd")) != -1)
		switch (ch) {
		case 'f':
			/*
			 * On Linux, "hostname -f" prints FQDN.
			 * BSD "hostname" always prints FQDN by
			 * default, so we accept but ignore -f.
			 */
			break;
		case 's':
			sflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc > 1 || (sflag && dflag))
		usage();

	if (*argv) {
		if (sethostname(*argv, (int)strlen(*argv)))
			err(1, "sethostname");
	} else {
		if (gethostname(hostname, (int)sizeof(hostname)))
			err(1, "gethostname");
		if (sflag) {
			p = strchr(hostname, '.');
			if (p != NULL)
				*p = '\0';
		} else if (dflag) {
			p = strchr(hostname, '.');
			if (p != NULL)
				strcpy(hostname, ++p);
		}
		(void)printf("%s\n", hostname);
	}
	exit(0);
}