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
struct virtnet_info {int /*<<< orphan*/  napi; int /*<<< orphan*/  refill; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int virtnet_close(struct net_device *dev)
{
	struct virtnet_info *vi = netdev_priv(dev);

	/* Make sure refill_work doesn't re-enable napi! */
	cancel_delayed_work_sync(&vi->refill);
	napi_disable(&vi->napi);

	return 0;
}