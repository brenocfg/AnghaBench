#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipw2100_priv {unsigned long reset_backoff; unsigned long last_reset; int status; TYPE_1__* net_dev; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  reset_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int /*<<< orphan*/ ,...) ; 
 int MAX_RESET_BACKOFF ; 
 int STATUS_RESET_PENDING ; 
 void* get_seconds () ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void schedule_reset(struct ipw2100_priv *priv)
{
	unsigned long now = get_seconds();

	/* If we haven't received a reset request within the backoff period,
	 * then we can reset the backoff interval so this reset occurs
	 * immediately */
	if (priv->reset_backoff &&
	    (now - priv->last_reset > priv->reset_backoff))
		priv->reset_backoff = 0;

	priv->last_reset = get_seconds();

	if (!(priv->status & STATUS_RESET_PENDING)) {
		IPW_DEBUG_INFO("%s: Scheduling firmware restart (%ds).\n",
			       priv->net_dev->name, priv->reset_backoff);
		netif_carrier_off(priv->net_dev);
		netif_stop_queue(priv->net_dev);
		priv->status |= STATUS_RESET_PENDING;
		if (priv->reset_backoff)
			schedule_delayed_work(&priv->reset_work,
					      priv->reset_backoff * HZ);
		else
			schedule_delayed_work(&priv->reset_work, 0);

		if (priv->reset_backoff < MAX_RESET_BACKOFF)
			priv->reset_backoff++;

		wake_up_interruptible(&priv->wait_command_queue);
	} else
		IPW_DEBUG_INFO("%s: Firmware restart already in progress.\n",
			       priv->net_dev->name);

}