#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smi_info {int msg_flags; void* si_state; scalar_t__ (* oem_data_avail_handler ) (struct smi_info*) ;TYPE_2__* curr_msg; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; int /*<<< orphan*/  intf; } ;
struct TYPE_4__ {int* data; int data_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int EVENT_MSG_BUFFER_FULL ; 
 int IPMI_GET_MSG_CMD ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_READ_EVENT_MSG_BUFFER_CMD ; 
 int OEM_DATA_AVAIL ; 
 int RECEIVE_MSG_AVAIL ; 
 void* SI_GETTING_EVENTS ; 
 void* SI_GETTING_MESSAGES ; 
 void* SI_NORMAL ; 
 int WDT_PRE_TIMEOUT_INT ; 
 int /*<<< orphan*/  disable_si_irq (struct smi_info*) ; 
 int /*<<< orphan*/  enable_si_irq (struct smi_info*) ; 
 void* ipmi_alloc_smi_msg () ; 
 int /*<<< orphan*/  ipmi_smi_watchdog_pretimeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_inc_stat (struct smi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_clear_flags (struct smi_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ stub3 (struct smi_info*) ; 
 int /*<<< orphan*/  watchdog_pretimeouts ; 

__attribute__((used)) static void handle_flags(struct smi_info *smi_info)
{
 retry:
	if (smi_info->msg_flags & WDT_PRE_TIMEOUT_INT) {
		/* Watchdog pre-timeout */
		smi_inc_stat(smi_info, watchdog_pretimeouts);

		start_clear_flags(smi_info);
		smi_info->msg_flags &= ~WDT_PRE_TIMEOUT_INT;
		ipmi_smi_watchdog_pretimeout(smi_info->intf);
	} else if (smi_info->msg_flags & RECEIVE_MSG_AVAIL) {
		/* Messages available. */
		smi_info->curr_msg = ipmi_alloc_smi_msg();
		if (!smi_info->curr_msg) {
			disable_si_irq(smi_info);
			smi_info->si_state = SI_NORMAL;
			return;
		}
		enable_si_irq(smi_info);

		smi_info->curr_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
		smi_info->curr_msg->data[1] = IPMI_GET_MSG_CMD;
		smi_info->curr_msg->data_size = 2;

		smi_info->handlers->start_transaction(
			smi_info->si_sm,
			smi_info->curr_msg->data,
			smi_info->curr_msg->data_size);
		smi_info->si_state = SI_GETTING_MESSAGES;
	} else if (smi_info->msg_flags & EVENT_MSG_BUFFER_FULL) {
		/* Events available. */
		smi_info->curr_msg = ipmi_alloc_smi_msg();
		if (!smi_info->curr_msg) {
			disable_si_irq(smi_info);
			smi_info->si_state = SI_NORMAL;
			return;
		}
		enable_si_irq(smi_info);

		smi_info->curr_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
		smi_info->curr_msg->data[1] = IPMI_READ_EVENT_MSG_BUFFER_CMD;
		smi_info->curr_msg->data_size = 2;

		smi_info->handlers->start_transaction(
			smi_info->si_sm,
			smi_info->curr_msg->data,
			smi_info->curr_msg->data_size);
		smi_info->si_state = SI_GETTING_EVENTS;
	} else if (smi_info->msg_flags & OEM_DATA_AVAIL &&
		   smi_info->oem_data_avail_handler) {
		if (smi_info->oem_data_avail_handler(smi_info))
			goto retry;
	} else
		smi_info->si_state = SI_NORMAL;
}