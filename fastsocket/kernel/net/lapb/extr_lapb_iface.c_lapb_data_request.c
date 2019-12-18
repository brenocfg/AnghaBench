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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct lapb_cb {scalar_t__ state; int /*<<< orphan*/  write_queue; } ;

/* Variables and functions */
 int LAPB_BADTOKEN ; 
 int LAPB_NOTCONNECTED ; 
 int LAPB_OK ; 
 scalar_t__ LAPB_STATE_3 ; 
 scalar_t__ LAPB_STATE_4 ; 
 struct lapb_cb* lapb_devtostruct (struct net_device*) ; 
 int /*<<< orphan*/  lapb_kick (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_put (struct lapb_cb*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int lapb_data_request(struct net_device *dev, struct sk_buff *skb)
{
	struct lapb_cb *lapb = lapb_devtostruct(dev);
	int rc = LAPB_BADTOKEN;

	if (!lapb)
		goto out;

	rc = LAPB_NOTCONNECTED;
	if (lapb->state != LAPB_STATE_3 && lapb->state != LAPB_STATE_4)
		goto out_put;

	skb_queue_tail(&lapb->write_queue, skb);
	lapb_kick(lapb);
	rc = LAPB_OK;
out_put:
	lapb_put(lapb);
out:
	return rc;
}