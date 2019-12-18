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
struct qib_pportdata {int /*<<< orphan*/  sdma_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_sdma (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_event_e00_go_hw_down ; 
 int /*<<< orphan*/  qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_finalput (int /*<<< orphan*/ *) ; 

void qib_teardown_sdma(struct qib_pportdata *ppd)
{
	qib_sdma_process_event(ppd, qib_sdma_event_e00_go_hw_down);

	/*
	 * This waits for the state machine to exit so it is not
	 * necessary to kill the sdma_sw_clean_up_task to make sure
	 * it is not running.
	 */
	sdma_finalput(&ppd->sdma_state);

	free_sdma(ppd);
}