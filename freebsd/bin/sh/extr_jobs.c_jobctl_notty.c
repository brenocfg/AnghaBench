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
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  iflag ; 
 int jobctl ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  out2fmt_flush (char*) ; 
 int /*<<< orphan*/  setsignal (int /*<<< orphan*/ ) ; 
 int ttyfd ; 

__attribute__((used)) static void
jobctl_notty(void)
{
	if (ttyfd >= 0) {
		close(ttyfd);
		ttyfd = -1;
	}
	if (!iflag) {
		setsignal(SIGTSTP);
		setsignal(SIGTTOU);
		setsignal(SIGTTIN);
		jobctl = 1;
		return;
	}
	out2fmt_flush("sh: can't access tty; job control turned off\n");
	mflag = 0;
}