#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct dst_entry {struct net_device* dev; TYPE_1__* neighbour; int /*<<< orphan*/  output; int /*<<< orphan*/  input; TYPE_2__* ops; } ;
struct TYPE_6__ {struct net_device* loopback_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ifdown ) (struct dst_entry*,struct net_device*,int) ;} ;
struct TYPE_4__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 TYPE_3__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dst_discard ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,struct net_device*,int) ; 

__attribute__((used)) static inline void dst_ifdown(struct dst_entry *dst, struct net_device *dev,
			      int unregister)
{
	if (dst->ops->ifdown)
		dst->ops->ifdown(dst, dev, unregister);

	if (dev != dst->dev)
		return;

	if (!unregister) {
		dst->input = dst->output = dst_discard;
	} else {
		dst->dev = dev_net(dst->dev)->loopback_dev;
		dev_hold(dst->dev);
		dev_put(dev);
		if (dst->neighbour && dst->neighbour->dev == dev) {
			dst->neighbour->dev = dst->dev;
			dev_hold(dst->dev);
			dev_put(dev);
		}
	}
}