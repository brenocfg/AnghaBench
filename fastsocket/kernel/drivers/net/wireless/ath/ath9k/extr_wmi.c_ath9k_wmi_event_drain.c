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
struct ath9k_htc_priv {TYPE_1__* wmi; } ;
struct TYPE_2__ {int /*<<< orphan*/  wmi_lock; int /*<<< orphan*/  wmi_event_queue; int /*<<< orphan*/  wmi_event_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void ath9k_wmi_event_drain(struct ath9k_htc_priv *priv)
{
	unsigned long flags;

	tasklet_kill(&priv->wmi->wmi_event_tasklet);
	spin_lock_irqsave(&priv->wmi->wmi_lock, flags);
	__skb_queue_purge(&priv->wmi->wmi_event_queue);
	spin_unlock_irqrestore(&priv->wmi->wmi_lock, flags);
}