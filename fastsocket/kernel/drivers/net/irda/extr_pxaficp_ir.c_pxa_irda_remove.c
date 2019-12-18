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
struct TYPE_6__ {int /*<<< orphan*/  head; } ;
struct TYPE_5__ {int /*<<< orphan*/  head; } ;
struct pxa_irda {int /*<<< orphan*/  sir_clk; int /*<<< orphan*/  fir_clk; TYPE_3__ rx_buff; TYPE_2__ tx_buff; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* shutdown ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  gpio_pwdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  FICP ; 
 int /*<<< orphan*/  STUART ; 
 int /*<<< orphan*/  __PREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct pxa_irda* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int pxa_irda_remove(struct platform_device *_dev)
{
	struct net_device *dev = platform_get_drvdata(_dev);

	if (dev) {
		struct pxa_irda *si = netdev_priv(dev);
		unregister_netdev(dev);
		if (gpio_is_valid(si->pdata->gpio_pwdown))
			gpio_free(si->pdata->gpio_pwdown);
		if (si->pdata->shutdown)
			si->pdata->shutdown(si->dev);
		kfree(si->tx_buff.head);
		kfree(si->rx_buff.head);
		clk_put(si->fir_clk);
		clk_put(si->sir_clk);
		free_netdev(dev);
	}

	release_mem_region(__PREG(STUART), 0x24);
	release_mem_region(__PREG(FICP), 0x1c);

	return 0;
}