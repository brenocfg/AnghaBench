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
 int SIGXCPU ; 
 int /*<<< orphan*/  ar_close () ; 
 int /*<<< orphan*/  atdir_end () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  paxwarn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  proc_dir () ; 
 scalar_t__ tflag ; 
 int vflag ; 
 int vfpart ; 

void
sig_cleanup(int which_sig)
{
	/*
	 * restore modes and times for any dirs we may have created
	 * or any dirs we may have read. Set vflag and vfpart so the user
	 * will clearly see the message on a line by itself.
	 */
	vflag = vfpart = 1;
	if (which_sig == SIGXCPU)
		paxwarn(0, "Cpu time limit reached, cleaning up.");
	else
		paxwarn(0, "Signal caught, cleaning up.");

	ar_close();
	proc_dir();
	if (tflag)
		atdir_end();
	exit(1);
}