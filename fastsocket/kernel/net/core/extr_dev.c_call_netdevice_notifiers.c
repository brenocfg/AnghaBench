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

/* Variables and functions */
 int /*<<< orphan*/  netdev_chain ; 
 int raw_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,struct net_device*) ; 

int call_netdevice_notifiers(unsigned long val, struct net_device *dev)
{
	return raw_notifier_call_chain(&netdev_chain, val, dev);
}