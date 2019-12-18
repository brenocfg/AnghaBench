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
 int /*<<< orphan*/  NCR5380_tqueue ; 
 int /*<<< orphan*/  main_running ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void queue_main(void)
{
    if (!main_running) {
	/* If in interrupt and NCR5380_main() not already running,
	   queue it on the 'immediate' task queue, to be processed
	   immediately after the current interrupt processing has
	   finished. */
	schedule_work(&NCR5380_tqueue);
    }
    /* else: nothing to do: the running NCR5380_main() will pick up
       any newly queued command. */
}