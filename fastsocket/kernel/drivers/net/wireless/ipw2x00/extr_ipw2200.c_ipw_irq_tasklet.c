#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ipw_priv {int isr_inta; int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  adapter_restart; int /*<<< orphan*/  wait_command_queue; TYPE_3__* ieee; struct ipw_fw_error* error; int /*<<< orphan*/  rf_kill; int /*<<< orphan*/  link_down; int /*<<< orphan*/  scan_event; int /*<<< orphan*/  request_passive_scan; int /*<<< orphan*/  request_direct_scan; int /*<<< orphan*/  request_scan; int /*<<< orphan*/ * txq; int /*<<< orphan*/  txq_cmd; int /*<<< orphan*/  irq_lock; } ;
struct ipw_fw_error {int dummy; } ;
struct TYPE_5__ {scalar_t__ encrypt; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_6__ {TYPE_2__ sec; TYPE_1__ wdev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_FW (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_RF_KILL (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_TX (char*) ; 
 int IPW_DL_FW_ERRORS ; 
 int /*<<< orphan*/  IPW_ERROR (char*,...) ; 
 int IPW_INTA_BIT_BEACON_PERIOD_EXPIRED ; 
 int IPW_INTA_BIT_FATAL_ERROR ; 
 int IPW_INTA_BIT_FW_CARD_DISABLE_PHY_OFF_DONE ; 
 int IPW_INTA_BIT_FW_INITIALIZATION_DONE ; 
 int IPW_INTA_BIT_PARITY_ERROR ; 
 int IPW_INTA_BIT_RF_KILL_DONE ; 
 int IPW_INTA_BIT_RX_TRANSFER ; 
 int IPW_INTA_BIT_SLAVE_MODE_HOST_CMD_DONE ; 
 int IPW_INTA_BIT_STATUS_CHANGE ; 
 int IPW_INTA_BIT_TX_CMD_QUEUE ; 
 int IPW_INTA_BIT_TX_QUEUE_1 ; 
 int IPW_INTA_BIT_TX_QUEUE_2 ; 
 int IPW_INTA_BIT_TX_QUEUE_3 ; 
 int IPW_INTA_BIT_TX_QUEUE_4 ; 
 int IPW_INTA_MASK_ALL ; 
 int /*<<< orphan*/  IPW_INTA_MASK_R ; 
 int /*<<< orphan*/  IPW_INTA_RW ; 
 int /*<<< orphan*/  IPW_WARNING (char*) ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_ASSOCIATING ; 
 int STATUS_HCMD_ACTIVE ; 
 int STATUS_INIT ; 
 int STATUS_RF_KILL_HW ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 void* ipw_alloc_error_log (struct ipw_priv*) ; 
 int ipw_debug_level ; 
 int /*<<< orphan*/  ipw_dump_error_log (struct ipw_priv*,struct ipw_fw_error*) ; 
 int /*<<< orphan*/  ipw_enable_interrupts (struct ipw_priv*) ; 
 int ipw_queue_tx_reclaim (struct ipw_priv*,int /*<<< orphan*/ *,int) ; 
 int ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_rx (struct ipw_priv*) ; 
 int /*<<< orphan*/  kfree (struct ipw_fw_error*) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct ipw_priv*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipw_irq_tasklet(struct ipw_priv *priv)
{
	u32 inta, inta_mask, handled = 0;
	unsigned long flags;
	int rc = 0;

	spin_lock_irqsave(&priv->irq_lock, flags);

	inta = ipw_read32(priv, IPW_INTA_RW);
	inta_mask = ipw_read32(priv, IPW_INTA_MASK_R);

	if (inta == 0xFFFFFFFF) {
		/* Hardware disappeared */
		IPW_WARNING("TASKLET INTA == 0xFFFFFFFF\n");
		/* Only handle the cached INTA values */
		inta = 0;
	}
	inta &= (IPW_INTA_MASK_ALL & inta_mask);

	/* Add any cached INTA values that need to be handled */
	inta |= priv->isr_inta;

	spin_unlock_irqrestore(&priv->irq_lock, flags);

	spin_lock_irqsave(&priv->lock, flags);

	/* handle all the justifications for the interrupt */
	if (inta & IPW_INTA_BIT_RX_TRANSFER) {
		ipw_rx(priv);
		handled |= IPW_INTA_BIT_RX_TRANSFER;
	}

	if (inta & IPW_INTA_BIT_TX_CMD_QUEUE) {
		IPW_DEBUG_HC("Command completed.\n");
		rc = ipw_queue_tx_reclaim(priv, &priv->txq_cmd, -1);
		priv->status &= ~STATUS_HCMD_ACTIVE;
		wake_up_interruptible(&priv->wait_command_queue);
		handled |= IPW_INTA_BIT_TX_CMD_QUEUE;
	}

	if (inta & IPW_INTA_BIT_TX_QUEUE_1) {
		IPW_DEBUG_TX("TX_QUEUE_1\n");
		rc = ipw_queue_tx_reclaim(priv, &priv->txq[0], 0);
		handled |= IPW_INTA_BIT_TX_QUEUE_1;
	}

	if (inta & IPW_INTA_BIT_TX_QUEUE_2) {
		IPW_DEBUG_TX("TX_QUEUE_2\n");
		rc = ipw_queue_tx_reclaim(priv, &priv->txq[1], 1);
		handled |= IPW_INTA_BIT_TX_QUEUE_2;
	}

	if (inta & IPW_INTA_BIT_TX_QUEUE_3) {
		IPW_DEBUG_TX("TX_QUEUE_3\n");
		rc = ipw_queue_tx_reclaim(priv, &priv->txq[2], 2);
		handled |= IPW_INTA_BIT_TX_QUEUE_3;
	}

	if (inta & IPW_INTA_BIT_TX_QUEUE_4) {
		IPW_DEBUG_TX("TX_QUEUE_4\n");
		rc = ipw_queue_tx_reclaim(priv, &priv->txq[3], 3);
		handled |= IPW_INTA_BIT_TX_QUEUE_4;
	}

	if (inta & IPW_INTA_BIT_STATUS_CHANGE) {
		IPW_WARNING("STATUS_CHANGE\n");
		handled |= IPW_INTA_BIT_STATUS_CHANGE;
	}

	if (inta & IPW_INTA_BIT_BEACON_PERIOD_EXPIRED) {
		IPW_WARNING("TX_PERIOD_EXPIRED\n");
		handled |= IPW_INTA_BIT_BEACON_PERIOD_EXPIRED;
	}

	if (inta & IPW_INTA_BIT_SLAVE_MODE_HOST_CMD_DONE) {
		IPW_WARNING("HOST_CMD_DONE\n");
		handled |= IPW_INTA_BIT_SLAVE_MODE_HOST_CMD_DONE;
	}

	if (inta & IPW_INTA_BIT_FW_INITIALIZATION_DONE) {
		IPW_WARNING("FW_INITIALIZATION_DONE\n");
		handled |= IPW_INTA_BIT_FW_INITIALIZATION_DONE;
	}

	if (inta & IPW_INTA_BIT_FW_CARD_DISABLE_PHY_OFF_DONE) {
		IPW_WARNING("PHY_OFF_DONE\n");
		handled |= IPW_INTA_BIT_FW_CARD_DISABLE_PHY_OFF_DONE;
	}

	if (inta & IPW_INTA_BIT_RF_KILL_DONE) {
		IPW_DEBUG_RF_KILL("RF_KILL_DONE\n");
		priv->status |= STATUS_RF_KILL_HW;
		wiphy_rfkill_set_hw_state(priv->ieee->wdev.wiphy, true);
		wake_up_interruptible(&priv->wait_command_queue);
		priv->status &= ~(STATUS_ASSOCIATED | STATUS_ASSOCIATING);
		cancel_delayed_work(&priv->request_scan);
		cancel_delayed_work(&priv->request_direct_scan);
		cancel_delayed_work(&priv->request_passive_scan);
		cancel_delayed_work(&priv->scan_event);
		schedule_work(&priv->link_down);
		schedule_delayed_work(&priv->rf_kill, 2 * HZ);
		handled |= IPW_INTA_BIT_RF_KILL_DONE;
	}

	if (inta & IPW_INTA_BIT_FATAL_ERROR) {
		IPW_WARNING("Firmware error detected.  Restarting.\n");
		if (priv->error) {
			IPW_DEBUG_FW("Sysfs 'error' log already exists.\n");
			if (ipw_debug_level & IPW_DL_FW_ERRORS) {
				struct ipw_fw_error *error =
				    ipw_alloc_error_log(priv);
				ipw_dump_error_log(priv, error);
				kfree(error);
			}
		} else {
			priv->error = ipw_alloc_error_log(priv);
			if (priv->error)
				IPW_DEBUG_FW("Sysfs 'error' log captured.\n");
			else
				IPW_DEBUG_FW("Error allocating sysfs 'error' "
					     "log.\n");
			if (ipw_debug_level & IPW_DL_FW_ERRORS)
				ipw_dump_error_log(priv, priv->error);
		}

		/* XXX: If hardware encryption is for WPA/WPA2,
		 * we have to notify the supplicant. */
		if (priv->ieee->sec.encrypt) {
			priv->status &= ~STATUS_ASSOCIATED;
			notify_wx_assoc_event(priv);
		}

		/* Keep the restart process from trying to send host
		 * commands by clearing the INIT status bit */
		priv->status &= ~STATUS_INIT;

		/* Cancel currently queued command. */
		priv->status &= ~STATUS_HCMD_ACTIVE;
		wake_up_interruptible(&priv->wait_command_queue);

		schedule_work(&priv->adapter_restart);
		handled |= IPW_INTA_BIT_FATAL_ERROR;
	}

	if (inta & IPW_INTA_BIT_PARITY_ERROR) {
		IPW_ERROR("Parity error\n");
		handled |= IPW_INTA_BIT_PARITY_ERROR;
	}

	if (handled != inta) {
		IPW_ERROR("Unhandled INTA bits 0x%08x\n", inta & ~handled);
	}

	spin_unlock_irqrestore(&priv->lock, flags);

	/* enable all interrupts */
	ipw_enable_interrupts(priv);
}