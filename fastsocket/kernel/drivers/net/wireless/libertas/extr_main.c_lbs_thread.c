#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {scalar_t__ currenttxskb; scalar_t__ psstate; scalar_t__ tx_pending_len; size_t resp_idx; scalar_t__ connect_status; int nr_retries; int (* hw_host_to_card ) (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ mesh_connect_status; int /*<<< orphan*/  cmd_pending; int /*<<< orphan*/  command_timer; int /*<<< orphan*/  driver_lock; scalar_t__ mesh_dev; scalar_t__ dev; void* dnld_sent; int /*<<< orphan*/  tx_pending_buf; int /*<<< orphan*/  cmdpendingq; struct cmd_ctrl_node* cur_cmd; int /*<<< orphan*/  fw_ready; int /*<<< orphan*/  event_fifo; scalar_t__ cmd_timed_out; int /*<<< orphan*/  (* reset_card ) (struct lbs_private*) ;scalar_t__* resp_len; int /*<<< orphan*/ * resp_buf; scalar_t__ surpriseremoved; int /*<<< orphan*/  waitq; void* psmode; } ;
struct cmd_ctrl_node {int /*<<< orphan*/  list; TYPE_1__* cmdbuf; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 void* DNLD_RES_RECEIVED ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_THREAD ; 
 int /*<<< orphan*/  MVMS_DAT ; 
 scalar_t__ PS_STATE_AWAKE ; 
 scalar_t__ PS_STATE_PRE_SLEEP ; 
 scalar_t__ PS_STATE_SLEEP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __kfifo_get (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ __kfifo_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  lbs_complete_command (struct lbs_private*,struct cmd_ctrl_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_thread (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_tx (char*,int) ; 
 int /*<<< orphan*/  lbs_execute_next_command (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_pr_alert (char*) ; 
 int /*<<< orphan*/  lbs_pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lbs_process_command_response (struct lbs_private*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lbs_process_event (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_ps_confirm_sleep (struct lbs_private*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (scalar_t__) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lbs_private*) ; 
 int stub2 (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_thread(void *data)
{
	struct net_device *dev = data;
	struct lbs_private *priv = dev->ml_priv;
	wait_queue_t wait;

	lbs_deb_enter(LBS_DEB_THREAD);

	init_waitqueue_entry(&wait, current);

	for (;;) {
		int shouldsleep;
		u8 resp_idx;

		lbs_deb_thread("1: currenttxskb %p, dnld_sent %d\n",
				priv->currenttxskb, priv->dnld_sent);

		add_wait_queue(&priv->waitq, &wait);
		set_current_state(TASK_INTERRUPTIBLE);
		spin_lock_irq(&priv->driver_lock);

		if (kthread_should_stop())
			shouldsleep = 0;	/* Bye */
		else if (priv->surpriseremoved)
			shouldsleep = 1;	/* We need to wait until we're _told_ to die */
		else if (priv->psstate == PS_STATE_SLEEP)
			shouldsleep = 1;	/* Sleep mode. Nothing we can do till it wakes */
		else if (priv->cmd_timed_out)
			shouldsleep = 0;	/* Command timed out. Recover */
		else if (!priv->fw_ready)
			shouldsleep = 1;	/* Firmware not ready. We're waiting for it */
		else if (priv->dnld_sent)
			shouldsleep = 1;	/* Something is en route to the device already */
		else if (priv->tx_pending_len > 0)
			shouldsleep = 0;	/* We've a packet to send */
		else if (priv->resp_len[priv->resp_idx])
			shouldsleep = 0;	/* We have a command response */
		else if (priv->cur_cmd)
			shouldsleep = 1;	/* Can't send a command; one already running */
		else if (!list_empty(&priv->cmdpendingq))
			shouldsleep = 0;	/* We have a command to send */
		else if (__kfifo_len(priv->event_fifo))
			shouldsleep = 0;	/* We have an event to process */
		else
			shouldsleep = 1;	/* No command */

		if (shouldsleep) {
			lbs_deb_thread("sleeping, connect_status %d, "
				"psmode %d, psstate %d\n",
				priv->connect_status,
				priv->psmode, priv->psstate);
			spin_unlock_irq(&priv->driver_lock);
			schedule();
		} else
			spin_unlock_irq(&priv->driver_lock);

		lbs_deb_thread("2: currenttxskb %p, dnld_send %d\n",
			       priv->currenttxskb, priv->dnld_sent);

		set_current_state(TASK_RUNNING);
		remove_wait_queue(&priv->waitq, &wait);

		lbs_deb_thread("3: currenttxskb %p, dnld_sent %d\n",
			       priv->currenttxskb, priv->dnld_sent);

		if (kthread_should_stop()) {
			lbs_deb_thread("break from main thread\n");
			break;
		}

		if (priv->surpriseremoved) {
			lbs_deb_thread("adapter removed; waiting to die...\n");
			continue;
		}

		lbs_deb_thread("4: currenttxskb %p, dnld_sent %d\n",
		       priv->currenttxskb, priv->dnld_sent);

		/* Process any pending command response */
		spin_lock_irq(&priv->driver_lock);
		resp_idx = priv->resp_idx;
		if (priv->resp_len[resp_idx]) {
			spin_unlock_irq(&priv->driver_lock);
			lbs_process_command_response(priv,
				priv->resp_buf[resp_idx],
				priv->resp_len[resp_idx]);
			spin_lock_irq(&priv->driver_lock);
			priv->resp_len[resp_idx] = 0;
		}
		spin_unlock_irq(&priv->driver_lock);

		/* command timeout stuff */
		if (priv->cmd_timed_out && priv->cur_cmd) {
			struct cmd_ctrl_node *cmdnode = priv->cur_cmd;

			if (++priv->nr_retries > 3) {
				lbs_pr_info("Excessive timeouts submitting "
					"command 0x%04x\n",
					le16_to_cpu(cmdnode->cmdbuf->command));
				lbs_complete_command(priv, cmdnode, -ETIMEDOUT);
				priv->nr_retries = 0;
				if (priv->reset_card)
					priv->reset_card(priv);
			} else {
				priv->cur_cmd = NULL;
				priv->dnld_sent = DNLD_RES_RECEIVED;
				lbs_pr_info("requeueing command 0x%04x due "
					"to timeout (#%d)\n",
					le16_to_cpu(cmdnode->cmdbuf->command),
					priv->nr_retries);

				/* Stick it back at the _top_ of the pending queue
				   for immediate resubmission */
				list_add(&cmdnode->list, &priv->cmdpendingq);
			}
		}
		priv->cmd_timed_out = 0;

		/* Process hardware events, e.g. card removed, link lost */
		spin_lock_irq(&priv->driver_lock);
		while (__kfifo_len(priv->event_fifo)) {
			u32 event;

			__kfifo_get(priv->event_fifo, (unsigned char *) &event,
				sizeof(event));
			spin_unlock_irq(&priv->driver_lock);
			lbs_process_event(priv, event);
			spin_lock_irq(&priv->driver_lock);
		}
		spin_unlock_irq(&priv->driver_lock);

		if (!priv->fw_ready)
			continue;

		/* Check if we need to confirm Sleep Request received previously */
		if (priv->psstate == PS_STATE_PRE_SLEEP &&
		    !priv->dnld_sent && !priv->cur_cmd) {
			if (priv->connect_status == LBS_CONNECTED) {
				lbs_deb_thread("pre-sleep, currenttxskb %p, "
					"dnld_sent %d, cur_cmd %p\n",
					priv->currenttxskb, priv->dnld_sent,
					priv->cur_cmd);

				lbs_ps_confirm_sleep(priv);
			} else {
				/* workaround for firmware sending
				 * deauth/linkloss event immediately
				 * after sleep request; remove this
				 * after firmware fixes it
				 */
				priv->psstate = PS_STATE_AWAKE;
				lbs_pr_alert("ignore PS_SleepConfirm in "
					"non-connected state\n");
			}
		}

		/* The PS state is changed during processing of Sleep Request
		 * event above
		 */
		if ((priv->psstate == PS_STATE_SLEEP) ||
		    (priv->psstate == PS_STATE_PRE_SLEEP))
			continue;

		/* Execute the next command */
		if (!priv->dnld_sent && !priv->cur_cmd)
			lbs_execute_next_command(priv);

		/* Wake-up command waiters which can't sleep in
		 * lbs_prepare_and_send_command
		 */
		if (!list_empty(&priv->cmdpendingq))
			wake_up_all(&priv->cmd_pending);

		spin_lock_irq(&priv->driver_lock);
		if (!priv->dnld_sent && priv->tx_pending_len > 0) {
			int ret = priv->hw_host_to_card(priv, MVMS_DAT,
							priv->tx_pending_buf,
							priv->tx_pending_len);
			if (ret) {
				lbs_deb_tx("host_to_card failed %d\n", ret);
				priv->dnld_sent = DNLD_RES_RECEIVED;
			}
			priv->tx_pending_len = 0;
			if (!priv->currenttxskb) {
				/* We can wake the queues immediately if we aren't
				   waiting for TX feedback */
				if (priv->connect_status == LBS_CONNECTED)
					netif_wake_queue(priv->dev);
				if (priv->mesh_dev &&
				    priv->mesh_connect_status == LBS_CONNECTED)
					netif_wake_queue(priv->mesh_dev);
			}
		}
		spin_unlock_irq(&priv->driver_lock);
	}

	del_timer(&priv->command_timer);
	wake_up_all(&priv->cmd_pending);

	lbs_deb_leave(LBS_DEB_THREAD);
	return 0;
}