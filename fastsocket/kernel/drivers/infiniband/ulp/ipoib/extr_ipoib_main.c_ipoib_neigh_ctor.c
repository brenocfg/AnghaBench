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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ipoib_neigh {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  list; int /*<<< orphan*/  queue; int /*<<< orphan*/  daddr; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipoib_cm_set (struct ipoib_neigh*,int /*<<< orphan*/ *) ; 
 struct ipoib_neigh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipoib_neigh *ipoib_neigh_ctor(u8 *daddr,
				      struct net_device *dev)
{
	struct ipoib_neigh *neigh;

	neigh = kzalloc(sizeof *neigh, GFP_ATOMIC);
	if (!neigh)
		return NULL;

	neigh->dev = dev;
	memcpy(&neigh->daddr, daddr, sizeof(neigh->daddr));
	skb_queue_head_init(&neigh->queue);
	INIT_LIST_HEAD(&neigh->list);
	ipoib_cm_set(neigh, NULL);
	/* one ref on behalf of the caller */
	atomic_set(&neigh->refcnt, 1);

	return neigh;
}