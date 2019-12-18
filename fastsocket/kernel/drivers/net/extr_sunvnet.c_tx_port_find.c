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
struct vnet_port {int dummy; } ;
struct vnet {int /*<<< orphan*/  lock; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct vnet_port* __tx_port_find (struct vnet*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct vnet_port *tx_port_find(struct vnet *vp, struct sk_buff *skb)
{
	struct vnet_port *ret;
	unsigned long flags;

	spin_lock_irqsave(&vp->lock, flags);
	ret = __tx_port_find(vp, skb);
	spin_unlock_irqrestore(&vp->lock, flags);

	return ret;
}