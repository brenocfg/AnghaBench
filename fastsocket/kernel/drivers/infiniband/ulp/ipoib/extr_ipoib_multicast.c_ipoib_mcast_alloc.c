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
struct net_device {int dummy; } ;
struct ipoib_mcast {int backoff; int /*<<< orphan*/  pkt_queue; int /*<<< orphan*/  neigh_list; int /*<<< orphan*/  list; int /*<<< orphan*/  created; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ipoib_mcast* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipoib_mcast *ipoib_mcast_alloc(struct net_device *dev,
					     int can_sleep)
{
	struct ipoib_mcast *mcast;

	mcast = kzalloc(sizeof *mcast, can_sleep ? GFP_KERNEL : GFP_ATOMIC);
	if (!mcast)
		return NULL;

	mcast->dev = dev;
	mcast->created = jiffies;
	mcast->backoff = 1;

	INIT_LIST_HEAD(&mcast->list);
	INIT_LIST_HEAD(&mcast->neigh_list);
	skb_queue_head_init(&mcast->pkt_queue);

	return mcast;
}