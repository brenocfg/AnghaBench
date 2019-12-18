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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fcoe_port {TYPE_1__ fcoe_pending_queue; } ;
struct fc_lport {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void fcoe_clean_pending_queue(struct fc_lport *lport)
{
	struct fcoe_port  *port = lport_priv(lport);
	struct sk_buff *skb;

	spin_lock_bh(&port->fcoe_pending_queue.lock);
	while ((skb = __skb_dequeue(&port->fcoe_pending_queue)) != NULL) {
		spin_unlock_bh(&port->fcoe_pending_queue.lock);
		kfree_skb(skb);
		spin_lock_bh(&port->fcoe_pending_queue.lock);
	}
	spin_unlock_bh(&port->fcoe_pending_queue.lock);
}