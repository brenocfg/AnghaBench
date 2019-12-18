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
struct beiscsi_hba {int /*<<< orphan*/  state; int /*<<< orphan*/  shost; } ;
struct be_async_event_link_state {int port_link_status; scalar_t__ port_fault; int /*<<< orphan*/  physical_port; } ;

/* Variables and functions */
 int ASYNC_EVENT_LINK_DOWN ; 
 int ASYNC_EVENT_LINK_UP ; 
 int ASYNC_EVENT_LOGICAL ; 
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_INIT ; 
 scalar_t__ BEISCSI_PHY_LINK_FAULT_NONE ; 
 int /*<<< orphan*/  BE_ADAPTER_LINK_DOWN ; 
 int /*<<< orphan*/  BE_ADAPTER_UP ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  be2iscsi_fail_session ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_for_each_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void beiscsi_async_link_state_process(struct beiscsi_hba *phba,
		struct be_async_event_link_state *evt)
{
	if ((evt->port_link_status == ASYNC_EVENT_LINK_DOWN) ||
	    ((evt->port_link_status & ASYNC_EVENT_LOGICAL) &&
	     (evt->port_fault != BEISCSI_PHY_LINK_FAULT_NONE))) {
		phba->state = BE_ADAPTER_LINK_DOWN;

		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_INIT,
			    "BC_%d : Link Down on Port %d\n",
			    evt->physical_port);

		iscsi_host_for_each_session(phba->shost,
					    be2iscsi_fail_session);
	} else if ((evt->port_link_status & ASYNC_EVENT_LINK_UP) ||
		    ((evt->port_link_status & ASYNC_EVENT_LOGICAL) &&
		     (evt->port_fault == BEISCSI_PHY_LINK_FAULT_NONE))) {
		phba->state = BE_ADAPTER_UP;

		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_INIT,
			    "BC_%d : Link UP on Port %d\n",
			    evt->physical_port);
	}
}