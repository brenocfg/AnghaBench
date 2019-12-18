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
struct ipw_priv {int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  adapter_restart; int /*<<< orphan*/  rf_kill; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_RF_KILL (char*) ; 
 int STATUS_RF_KILL_MASK ; 
 scalar_t__ rf_kill_active (struct ipw_priv*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipw_rf_kill(void *adapter)
{
	struct ipw_priv *priv = adapter;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	if (rf_kill_active(priv)) {
		IPW_DEBUG_RF_KILL("RF Kill active, rescheduling GPIO check\n");
		schedule_delayed_work(&priv->rf_kill, 2 * HZ);
		goto exit_unlock;
	}

	/* RF Kill is now disabled, so bring the device back up */

	if (!(priv->status & STATUS_RF_KILL_MASK)) {
		IPW_DEBUG_RF_KILL("HW RF Kill no longer active, restarting "
				  "device\n");

		/* we can not do an adapter restart while inside an irq lock */
		schedule_work(&priv->adapter_restart);
	} else
		IPW_DEBUG_RF_KILL("HW RF Kill deactivated.  SW RF Kill still "
				  "enabled\n");

      exit_unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
}