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
struct virtnet_info {int /*<<< orphan*/  refill; int /*<<< orphan*/  st_wq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_fill_recv (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtnet_napi_enable (struct virtnet_info*) ; 

__attribute__((used)) static int virtnet_open(struct net_device *dev)
{
	struct virtnet_info *vi = netdev_priv(dev);

	/* Make sure we have some buffers: if oom use wq. */
	if (!try_fill_recv(vi, GFP_KERNEL))
		queue_delayed_work(vi->st_wq, &vi->refill, 0);

	virtnet_napi_enable(vi);
	return 0;
}