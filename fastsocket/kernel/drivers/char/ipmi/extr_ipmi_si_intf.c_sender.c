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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct smi_info {scalar_t__ si_state; int /*<<< orphan*/  si_lock; scalar_t__ thread; int /*<<< orphan*/  si_timer; scalar_t__ last_timeout_jiffies; int /*<<< orphan*/ * curr_msg; int /*<<< orphan*/  xmit_msgs; int /*<<< orphan*/  hp_xmit_msgs; scalar_t__ run_to_completion; int /*<<< orphan*/  stop_operation; } ;
struct ipmi_smi_msg {int* rsp; int* data; int rsp_size; int /*<<< orphan*/  link; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;

/* Variables and functions */
 int IPMI_ERR_UNSPECIFIED ; 
 scalar_t__ SI_NORMAL ; 
 int /*<<< orphan*/  SI_SHORT_TIMEOUT_USEC ; 
 int SI_SM_IDLE ; 
 scalar_t__ SI_TIMEOUT_JIFFIES ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deliver_recv_msg (struct smi_info*,struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smi_event_handler (struct smi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_next_msg (struct smi_info*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void sender(void                *send_info,
		   struct ipmi_smi_msg *msg,
		   int                 priority)
{
	struct smi_info   *smi_info = send_info;
	enum si_sm_result result;
	unsigned long     flags;
#ifdef DEBUG_TIMING
	struct timeval    t;
#endif

	if (atomic_read(&smi_info->stop_operation)) {
		msg->rsp[0] = msg->data[0] | 4;
		msg->rsp[1] = msg->data[1];
		msg->rsp[2] = IPMI_ERR_UNSPECIFIED;
		msg->rsp_size = 3;
		deliver_recv_msg(smi_info, msg);
		return;
	}

#ifdef DEBUG_TIMING
	do_gettimeofday(&t);
	printk("**Enqueue: %d.%9.9d\n", t.tv_sec, t.tv_usec);
#endif

	if (smi_info->run_to_completion) {
		/*
		 * If we are running to completion, then throw it in
		 * the list and run transactions until everything is
		 * clear.  Priority doesn't matter here.
		 */

		/*
		 * Run to completion means we are single-threaded, no
		 * need for locks.
		 */
		list_add_tail(&(msg->link), &(smi_info->xmit_msgs));

		result = smi_event_handler(smi_info, 0);
		while (result != SI_SM_IDLE) {
			udelay(SI_SHORT_TIMEOUT_USEC);
			result = smi_event_handler(smi_info,
						   SI_SHORT_TIMEOUT_USEC);
		}
		return;
	}

	spin_lock_irqsave(&smi_info->si_lock, flags);
	if (priority > 0)
		list_add_tail(&msg->link, &smi_info->hp_xmit_msgs);
	else
		list_add_tail(&msg->link, &smi_info->xmit_msgs);

	if (smi_info->si_state == SI_NORMAL && smi_info->curr_msg == NULL) {
		/*
		 * last_timeout_jiffies is updated here to avoid
		 * smi_timeout() handler passing very large time_diff
		 * value to smi_event_handler() that causes
		 * the send command to abort.
		 */
		smi_info->last_timeout_jiffies = jiffies;

		mod_timer(&smi_info->si_timer, jiffies + SI_TIMEOUT_JIFFIES);

		if (smi_info->thread)
			wake_up_process(smi_info->thread);

		start_next_msg(smi_info);
		smi_event_handler(smi_info, 0);
	}
	spin_unlock_irqrestore(&smi_info->si_lock, flags);
}