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
struct bpqdev {int /*<<< orphan*/  bpq_list; int /*<<< orphan*/  ethdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct bpqdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static void bpq_free_device(struct net_device *ndev)
{
	struct bpqdev *bpq = netdev_priv(ndev);

	dev_put(bpq->ethdev);
	list_del_rcu(&bpq->bpq_list);

	unregister_netdevice(ndev);
}