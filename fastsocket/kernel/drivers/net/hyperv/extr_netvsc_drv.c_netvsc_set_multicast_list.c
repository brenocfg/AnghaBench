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
struct net_device_context {int /*<<< orphan*/  work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netvsc_set_multicast_list(struct net_device *net)
{
	struct net_device_context *net_device_ctx = netdev_priv(net);

	schedule_work(&net_device_ctx->work);
}