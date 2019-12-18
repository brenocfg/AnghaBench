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
struct netdev_queue {int /*<<< orphan*/  _xmit_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_netdev_xmit_lock_key ; 

__attribute__((used)) static void nr_set_lockdep_one(struct net_device *dev,
			       struct netdev_queue *txq,
			       void *_unused)
{
	lockdep_set_class(&txq->_xmit_lock, &nr_netdev_xmit_lock_key);
}