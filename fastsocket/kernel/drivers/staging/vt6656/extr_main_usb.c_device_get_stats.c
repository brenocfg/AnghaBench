#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device_stats {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device_stats stats; } ;
typedef  TYPE_1__* PSDevice ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *device_get_stats(struct net_device *dev) {
    PSDevice pDevice=(PSDevice) netdev_priv(dev);

    return &pDevice->stats;
}