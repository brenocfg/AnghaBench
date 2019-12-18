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
 scalar_t__ ABORT_WAIT ; 
 int /*<<< orphan*/  Job_CatchOutput () ; 
 scalar_t__ aborting ; 
 scalar_t__ jobTokensRunning ; 

void
Job_Wait(void)
{
    aborting = ABORT_WAIT;
    while (jobTokensRunning != 0) {
	Job_CatchOutput();
    }
    aborting = 0;
}