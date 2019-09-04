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
 char* PROG_NAME ; 
 int PROG_VMAJOR ; 
 int PROG_VMINOR ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage_main(const char *progname, const char *msg, int verbose)
{
	const char *nm = basename((char *)progname);

	if (msg)
		printf("%s\n\n", msg);

	printf("%s v%d.%d\n", PROG_NAME, PROG_VMAJOR, PROG_VMINOR);
	printf("usage: %s [op] [-v] [-i id] [-t type] [-p pid] [-u uid] [-g gid] [-l login] [-G {groupspec}] [-m gmuid]\n", nm);
	if (!verbose)
		exit(1);

	printf("\t%-15s\tOne of: create | destroy | lookup | support\n", "[op]");
	printf("\t%-15s\tBe verbose\n", "-v");

	printf("\t%-15s\tID of the persona\n", "-i id");
	printf("\t%-15s\tType of the persona\n", "-t type");
	printf("\t%-15s\tPID of the process whose persona info to lookup\n", "-p pid");
	printf("\t%-15s\tUID to use in lookup\n", "-u uid");
	printf("\t%-15s\tGID of the persona\n", "-g gid");
	printf("\t%-15s\tLogin name of the persona\n", "-l login");
	printf("\t%-15s\tGroups to which the persona will belong\n", "-G {groupspec}");
	printf("\t%-15s\tgroupspec: G1{,G2,G3...}\n", " ");
	printf("\t%-15s\tUID used for memberd lookup (opt-in to memberd)\n", "-m gmuid");

	printf("\n");
	exit(1);
}