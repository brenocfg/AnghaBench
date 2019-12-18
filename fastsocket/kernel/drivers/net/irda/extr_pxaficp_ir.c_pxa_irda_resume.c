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
struct pxa_irda {int dummy; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct pxa_irda* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxa_irda_startup (struct pxa_irda*) ; 

__attribute__((used)) static int pxa_irda_resume(struct platform_device *_dev)
{
	struct net_device *dev = platform_get_drvdata(_dev);
	struct pxa_irda *si;

	if (dev && netif_running(dev)) {
		si = netdev_priv(dev);
		pxa_irda_startup(si);
		netif_device_attach(dev);
		netif_wake_queue(dev);
	}

	return 0;
}