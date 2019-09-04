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
typedef  int /*<<< orphan*/  uint64_t ;
struct sigaction {scalar_t__ sa_mask; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int TESTS ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char*) ; 
 char* error ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ test_alloc_dealloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_signal_handler ; 
 int /*<<< orphan*/  testit (int) ; 

int main(int argc, char **argv) {
	int i;
	uint64_t time1, time2;

	int mode = 0;
	if (argc>1) {
		if (!strcmp(argv[1], "-h")) {
			printf("Usage: %s <mode>\n", argv[0]);
			printf("\tmode = 0:  test all cases\n");
			printf("\tmode = -1: allocate/deallocate until failure\n");
			printf("\tmode > 0:  run test <tmode>\n");
			exit(0);
		}
		mode=atoi(argv[1]);
	}
	
	/* install SIGBUS handler */
	struct sigaction my_sigaction;
	my_sigaction.sa_handler = test_signal_handler;
	my_sigaction.sa_flags = SA_RESTART;
	my_sigaction.sa_mask = 0;
	sigaction( SIGBUS, &my_sigaction, NULL );
	sigaction( SIGSEGV, &my_sigaction, NULL );
	
	if (mode>0)		/* one specific test */
		testit(mode-1);

	if (mode==0) {	/* test all cases */
		printf("Running %d tests:\n", TESTS);
		for (i=0; i<TESTS; i++) {
			testit(i);
		}
	}
	if (mode==-1) {	/* alloc/dealloc */
			boolean_t ret;
		do {
			ret = test_alloc_dealloc(TRUE);
			printf(".");
			fflush(stdout);
		} while (ret);
		if (error[0])
			printf (" (%s)\n", error);
	}
	return 0;
}