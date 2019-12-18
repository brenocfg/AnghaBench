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
 int /*<<< orphan*/  ULI526X_DBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  uli526x_init (struct net_device*) ; 
 int /*<<< orphan*/  uli526x_reset_prepare (struct net_device*) ; 

__attribute__((used)) static void uli526x_dynamic_reset(struct net_device *dev)
{
	ULI526X_DBUG(0, "uli526x_dynamic_reset()", 0);

	uli526x_reset_prepare(dev);

	/* Re-initialize ULI526X board */
	uli526x_init(dev);

	/* Restart upper layer interface */
	netif_wake_queue(dev);
}