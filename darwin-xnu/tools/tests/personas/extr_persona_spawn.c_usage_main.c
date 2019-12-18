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
 char* PERSONA_TEST_NAME ; 
 int PERSONA_TEST_VMAJOR ; 
 int PERSONA_TEST_VMINOR ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage_main(const char *progname, int verbose)
{
	const char *nm = basename((char *)progname);

	printf("%s v%d.%d\n", PERSONA_TEST_NAME, PERSONA_TEST_VMAJOR, PERSONA_TEST_VMINOR);
	printf("usage: %s [-I id] [-V] [-u uid] [-g gid] [-vw] progname [args...]\n", nm);
	printf("       Spawn a new process into a new or existing persona.\n");
	if (!verbose)
		exit(1);

	printf("\t%-10s\tID of the persona\n", "-I id");
	printf("\t%-10s\tVerify persona parameters against existing persona (given by -I)\n", "-V");
	printf("\t%-10s\tOverride/verify the user ID of the new process\n", "-u uid");
	printf("\t%-10s\tOverride/verify the group ID of the new process\n", "-g gid");
	printf("\t%-15s\tGroups to which the persona will belong\n", "-G {groupspec}");
	printf("\t%-15s\tgroupspec: G1{,G2,G3...}\n", " ");
	printf("\t%-10s\tBe verbose\n", "-v");
	printf("\t%-10s\tDo not wait for the child process\n", "-w");
	printf("\n");

	exit(1);
}