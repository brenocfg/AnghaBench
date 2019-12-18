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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct bnad {int /*<<< orphan*/  bna_lock; } ;

/* Variables and functions */
 int bnad_mac_addr_set_locked (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bnad_set_mac_address(struct net_device *netdev, void *mac_addr)
{
	int err;
	struct bnad *bnad = netdev_priv(netdev);
	struct sockaddr *sa = (struct sockaddr *)mac_addr;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);

	err = bnad_mac_addr_set_locked(bnad, sa->sa_data);

	if (!err)
		memcpy(netdev->dev_addr, sa->sa_data, netdev->addr_len);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	return err;
}