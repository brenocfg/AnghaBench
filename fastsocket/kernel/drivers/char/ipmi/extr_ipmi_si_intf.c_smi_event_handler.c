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
struct smi_info {int /*<<< orphan*/  si_state; TYPE_2__* curr_msg; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; int /*<<< orphan*/  req_events; int /*<<< orphan*/  intf; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;
struct TYPE_4__ {int* data; int data_size; } ;
struct TYPE_3__ {int (* event ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_ERR_UNSPECIFIED ; 
 unsigned char IPMI_GET_MSG_FLAGS_CMD ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_READ_EVENT_MSG_BUFFER_CMD ; 
 int /*<<< orphan*/  SI_GETTING_EVENTS ; 
 int /*<<< orphan*/  SI_GETTING_FLAGS ; 
 int /*<<< orphan*/  SI_NORMAL ; 
 int SI_SM_ATTN ; 
 int SI_SM_CALL_WITHOUT_DELAY ; 
 int SI_SM_HOSED ; 
 int SI_SM_IDLE ; 
 int SI_SM_TRANSACTION_COMPLETE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attentions ; 
 int /*<<< orphan*/  complete_transactions ; 
 int /*<<< orphan*/  handle_transaction_done (struct smi_info*) ; 
 int /*<<< orphan*/  hosed_count ; 
 int /*<<< orphan*/  idles ; 
 TYPE_2__* ipmi_alloc_smi_msg () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_hosed_msg (struct smi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_inc_stat (struct smi_info*,int /*<<< orphan*/ ) ; 
 int start_next_msg (struct smi_info*) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,int) ; 
 int stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static enum si_sm_result smi_event_handler(struct smi_info *smi_info,
					   int time)
{
	enum si_sm_result si_sm_result;

 restart:
	/*
	 * There used to be a loop here that waited a little while
	 * (around 25us) before giving up.  That turned out to be
	 * pointless, the minimum delays I was seeing were in the 300us
	 * range, which is far too long to wait in an interrupt.  So
	 * we just run until the state machine tells us something
	 * happened or it needs a delay.
	 */
	si_sm_result = smi_info->handlers->event(smi_info->si_sm, time);
	time = 0;
	while (si_sm_result == SI_SM_CALL_WITHOUT_DELAY)
		si_sm_result = smi_info->handlers->event(smi_info->si_sm, 0);

	if (si_sm_result == SI_SM_TRANSACTION_COMPLETE) {
		smi_inc_stat(smi_info, complete_transactions);

		handle_transaction_done(smi_info);
		si_sm_result = smi_info->handlers->event(smi_info->si_sm, 0);
	} else if (si_sm_result == SI_SM_HOSED) {
		smi_inc_stat(smi_info, hosed_count);

		/*
		 * Do the before return_hosed_msg, because that
		 * releases the lock.
		 */
		smi_info->si_state = SI_NORMAL;
		if (smi_info->curr_msg != NULL) {
			/*
			 * If we were handling a user message, format
			 * a response to send to the upper layer to
			 * tell it about the error.
			 */
			return_hosed_msg(smi_info, IPMI_ERR_UNSPECIFIED);
		}
		si_sm_result = smi_info->handlers->event(smi_info->si_sm, 0);
	}

	/*
	 * We prefer handling attn over new messages.  But don't do
	 * this if there is not yet an upper layer to handle anything.
	 */
	if (likely(smi_info->intf) && si_sm_result == SI_SM_ATTN) {
		unsigned char msg[2];

		smi_inc_stat(smi_info, attentions);

		/*
		 * Got a attn, send down a get message flags to see
		 * what's causing it.  It would be better to handle
		 * this in the upper layer, but due to the way
		 * interrupts work with the SMI, that's not really
		 * possible.
		 */
		msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
		msg[1] = IPMI_GET_MSG_FLAGS_CMD;

		smi_info->handlers->start_transaction(
			smi_info->si_sm, msg, 2);
		smi_info->si_state = SI_GETTING_FLAGS;
		goto restart;
	}

	/* If we are currently idle, try to start the next message. */
	if (si_sm_result == SI_SM_IDLE) {
		smi_inc_stat(smi_info, idles);

		si_sm_result = start_next_msg(smi_info);
		if (si_sm_result != SI_SM_IDLE)
			goto restart;
	}

	if ((si_sm_result == SI_SM_IDLE)
	    && (atomic_read(&smi_info->req_events))) {
		/*
		 * We are idle and the upper layer requested that I fetch
		 * events, so do so.
		 */
		atomic_set(&smi_info->req_events, 0);

		smi_info->curr_msg = ipmi_alloc_smi_msg();
		if (!smi_info->curr_msg)
			goto out;

		smi_info->curr_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
		smi_info->curr_msg->data[1] = IPMI_READ_EVENT_MSG_BUFFER_CMD;
		smi_info->curr_msg->data_size = 2;

		smi_info->handlers->start_transaction(
			smi_info->si_sm,
			smi_info->curr_msg->data,
			smi_info->curr_msg->data_size);
		smi_info->si_state = SI_GETTING_EVENTS;
		goto restart;
	}
 out:
	return si_sm_result;
}