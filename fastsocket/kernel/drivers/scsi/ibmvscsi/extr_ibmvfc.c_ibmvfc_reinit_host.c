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
struct ibmvfc_host {scalar_t__ action; int reinit; int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ IBMVFC_HOST_ACTION_NONE ; 
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_QUERY ; 
 int /*<<< orphan*/  IBMVFC_INITIALIZING ; 
 int /*<<< orphan*/  ibmvfc_set_host_action (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_host_state (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_reinit_host(struct ibmvfc_host *vhost)
{
	if (vhost->action == IBMVFC_HOST_ACTION_NONE) {
		if (!ibmvfc_set_host_state(vhost, IBMVFC_INITIALIZING)) {
			scsi_block_requests(vhost->host);
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_QUERY);
		}
	} else
		vhost->reinit = 1;

	wake_up(&vhost->work_wait_q);
}