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
struct tasklet_completion_status {int /*<<< orphan*/  tmf_state; } ;
struct asd_ascb {int /*<<< orphan*/  completion; struct tasklet_completion_status* uldd_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 int /*<<< orphan*/  TMF_RESP_FUNC_FAILED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asd_tmf_timedout(unsigned long data)
{
	struct asd_ascb *ascb = (void *) data;
	struct tasklet_completion_status *tcs = ascb->uldd_task;

	ASD_DPRINTK("tmf timed out\n");
	tcs->tmf_state = TMF_RESP_FUNC_FAILED;
	complete(ascb->completion);
}