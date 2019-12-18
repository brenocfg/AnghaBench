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
 int /*<<< orphan*/  TRACE (char*) ; 
 int exiting ; 
 int exiting_exitstatus ; 
 int /*<<< orphan*/  exitshell_savedstatus () ; 
 int /*<<< orphan*/  getpid () ; 

void
exitshell(int status)
{
	TRACE(("exitshell(%d) pid=%d\n", status, getpid()));
	exiting = 1;
	exiting_exitstatus = status;
	exitshell_savedstatus();
}