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
struct notifier_block {int dummy; } ;
struct netlbl_unlhsh_iface {int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; scalar_t__ valid; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlbl_unlhsh_free_iface ; 
 int /*<<< orphan*/  netlbl_unlhsh_lock ; 
 struct netlbl_unlhsh_iface* netlbl_unlhsh_search_iface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlbl_unlhsh_netdev_handler(struct notifier_block *this,
					unsigned long event,
					void *ptr)
{
	struct net_device *dev = ptr;
	struct netlbl_unlhsh_iface *iface = NULL;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	/* XXX - should this be a check for NETDEV_DOWN or _UNREGISTER? */
	if (event == NETDEV_DOWN) {
		spin_lock(&netlbl_unlhsh_lock);
		iface = netlbl_unlhsh_search_iface(dev->ifindex);
		if (iface != NULL && iface->valid) {
			iface->valid = 0;
			list_del_rcu(&iface->list);
		} else
			iface = NULL;
		spin_unlock(&netlbl_unlhsh_lock);
	}

	if (iface != NULL)
		call_rcu(&iface->rcu, netlbl_unlhsh_free_iface);

	return NOTIFY_DONE;
}