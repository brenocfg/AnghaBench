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
typedef  int /*<<< orphan*/  domainname ;

/* Variables and functions */
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getdomainname (char*,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ setdomainname (char*,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch;
	char domainname[MAXHOSTNAMELEN];

	while ((ch = getopt(argc, argv, "")) != -1)
		switch (ch) {
		case '?':
			/* fall through */
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc > 1)
		usage();

	if (*argv) {
		if (setdomainname(*argv, (int)strlen(*argv)))
			err(1, "setdomainname");
	} else {
		if (getdomainname(domainname, (int)sizeof(domainname)))
			err(1, "getdomainname");
		(void)printf("%s\n", domainname);
	}
	exit(0);
}