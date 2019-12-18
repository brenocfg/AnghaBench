#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  head; } ;
struct TYPE_3__ {int /*<<< orphan*/  head; } ;
struct sa1100_irda {TYPE_2__ rx_buff; TYPE_1__ tx_buff; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Ser2HSCR0 ; 
 int /*<<< orphan*/  Ser2HSCR2 ; 
 int /*<<< orphan*/  Ser2UTCR0 ; 
 int /*<<< orphan*/  __PREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct sa1100_irda* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int sa1100_irda_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);

	if (dev) {
		struct sa1100_irda *si = netdev_priv(dev);
		unregister_netdev(dev);
		kfree(si->tx_buff.head);
		kfree(si->rx_buff.head);
		free_netdev(dev);
	}

	release_mem_region(__PREG(Ser2HSCR2), 0x04);
	release_mem_region(__PREG(Ser2HSCR0), 0x1c);
	release_mem_region(__PREG(Ser2UTCR0), 0x24);

	return 0;
}