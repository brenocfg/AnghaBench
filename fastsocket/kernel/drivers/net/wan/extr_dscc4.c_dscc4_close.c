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
struct dscc4_dev_priv {int /*<<< orphan*/  flags; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR0 ; 
 int /*<<< orphan*/  CCR2 ; 
 int /*<<< orphan*/  FakeReset ; 
 int /*<<< orphan*/  IMR ; 
 int PowerUp ; 
 int Vis ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct dscc4_dev_priv* dscc4_priv (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_close (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  scc_patchl (int,int /*<<< orphan*/ ,struct dscc4_dev_priv*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_writel (int,struct dscc4_dev_priv*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dscc4_close(struct net_device *dev)
{
	struct dscc4_dev_priv *dpriv = dscc4_priv(dev);

	del_timer_sync(&dpriv->timer);
	netif_stop_queue(dev);

	scc_patchl(PowerUp | Vis, 0, dpriv, dev, CCR0);
	scc_patchl(0x00050000, 0, dpriv, dev, CCR2);
	scc_writel(0xffffffff, dpriv, dev, IMR);

	dpriv->flags |= FakeReset;

	hdlc_close(dev);

	return 0;
}