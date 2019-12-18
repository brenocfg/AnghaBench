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
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct ax_device {int /*<<< orphan*/  mem2; scalar_t__ map2; int /*<<< orphan*/  mem; } ;
struct TYPE_2__ {scalar_t__ mem; } ;

/* Variables and functions */
 TYPE_1__ ei_status ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ax_remove(struct platform_device *_dev)
{
	struct net_device *dev = platform_get_drvdata(_dev);
	struct ax_device  *ax;

	ax = to_ax_dev(dev);

	unregister_netdev(dev);
	free_irq(dev->irq, dev);

	iounmap(ei_status.mem);
	release_resource(ax->mem);
	kfree(ax->mem);

	if (ax->map2) {
		iounmap(ax->map2);
		release_resource(ax->mem2);
		kfree(ax->mem2);
	}

	free_netdev(dev);

	return 0;
}