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
struct pcpu_lstats {int dummy; } ;
struct net_device {struct pcpu_lstats* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (struct pcpu_lstats*) ; 

__attribute__((used)) static void loopback_dev_free(struct net_device *dev)
{
	struct pcpu_lstats *lstats = dev->ml_priv;

	free_percpu(lstats);
	free_netdev(dev);
}