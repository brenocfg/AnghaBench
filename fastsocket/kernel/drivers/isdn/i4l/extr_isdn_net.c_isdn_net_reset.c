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
struct concap_proto {TYPE_2__* pops; } ;
struct concap_device_ops {int dummy; } ;
struct TYPE_6__ {TYPE_1__* netdev; struct concap_device_ops* dops; } ;
typedef  TYPE_3__ isdn_net_local ;
struct TYPE_5__ {int /*<<< orphan*/  (* restart ) (struct concap_proto*,struct net_device*,struct concap_device_ops*) ;} ;
struct TYPE_4__ {struct concap_proto* cprot; } ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct concap_proto*,struct net_device*,struct concap_device_ops*) ; 

__attribute__((used)) static void
isdn_net_reset(struct net_device *dev)
{
#ifdef CONFIG_ISDN_X25
	struct concap_device_ops * dops =
		((isdn_net_local *) netdev_priv(dev))->dops;
	struct concap_proto * cprot =
		((isdn_net_local *) netdev_priv(dev))->netdev->cprot;
#endif
#ifdef CONFIG_ISDN_X25
	if( cprot && cprot -> pops && dops )
		cprot -> pops -> restart ( cprot, dev, dops );
#endif
}