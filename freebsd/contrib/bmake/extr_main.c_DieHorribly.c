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
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRAPH2 ; 
 int /*<<< orphan*/  Job_AbortAll () ; 
 int /*<<< orphan*/  MAKEERROR ; 
 int /*<<< orphan*/  Targ_PrintGraph (int) ; 
 int /*<<< orphan*/  Trace_Log (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ jobsRunning ; 

void
DieHorribly(void)
{
	if (jobsRunning)
		Job_AbortAll();
	if (DEBUG(GRAPH2))
		Targ_PrintGraph(2);
	Trace_Log(MAKEERROR, 0);
	exit(2);		/* Not 1, so -q can distinguish error */
}