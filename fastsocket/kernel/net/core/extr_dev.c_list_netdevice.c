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
struct net_device {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  index_hlist; int /*<<< orphan*/  name; int /*<<< orphan*/  name_hlist; int /*<<< orphan*/  dev_list; } ;
struct net {int /*<<< orphan*/  dev_base_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  dev_base_lock ; 
 int /*<<< orphan*/  dev_index_hash (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name_hash (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int list_netdevice(struct net_device *dev)
{
	struct net *net = dev_net(dev);

	ASSERT_RTNL();

	write_lock_bh(&dev_base_lock);
	list_add_tail(&dev->dev_list, &net->dev_base_head);
	hlist_add_head(&dev->name_hlist, dev_name_hash(net, dev->name));
	hlist_add_head(&dev->index_hlist, dev_index_hash(net, dev->ifindex));
	write_unlock_bh(&dev_base_lock);
	return 0;
}