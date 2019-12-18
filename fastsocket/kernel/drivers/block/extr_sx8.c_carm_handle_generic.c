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
struct carm_request {int dummy; } ;
struct carm_host {int state; int /*<<< orphan*/  fsm_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int HST_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  carm_end_rq (struct carm_host*,struct carm_request*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void carm_handle_generic(struct carm_host *host,
				struct carm_request *crq, int error,
				int cur_state, int next_state)
{
	DPRINTK("ENTER\n");

	carm_end_rq(host, crq, error);

	assert(host->state == cur_state);
	if (error)
		host->state = HST_ERROR;
	else
		host->state = next_state;
	schedule_work(&host->fsm_task);
}