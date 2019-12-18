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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  exit_cleanup () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sigemptyset (int /*<<< orphan*/ *) ; 

void init_signal(void)
{
	sigset_t siglist;

	if(sigemptyset(&siglist) == -1) {
		perror("Unable to initialize signal list");
		exit_cleanup();
	}

	if(sigaddset(&siglist, SIGALRM) == -1) {
		perror("Unable to add SIGALRM signal to signal list");
		exit_cleanup();
	}

	if(sigaddset(&siglist, SIGINT) == -1) {
		perror("Unable to add SIGINT signal to signal list");
		exit_cleanup();
	}

	if(pthread_sigmask(SIG_BLOCK, &siglist, NULL) != 0) {
		perror("Unable to change signal mask");
		exit_cleanup();
	}
}