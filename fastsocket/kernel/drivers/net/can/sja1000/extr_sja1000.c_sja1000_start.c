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
struct TYPE_2__ {scalar_t__ state; } ;
struct sja1000_priv {int /*<<< orphan*/  (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ,int) ;TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  REG_ECC ; 
 int /*<<< orphan*/  REG_RXERR ; 
 int /*<<< orphan*/  REG_TXERR ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_normal_mode (struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sja1000_start(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);

	/* leave reset mode */
	if (priv->can.state != CAN_STATE_STOPPED)
		set_reset_mode(dev);

	/* Clear error counters and error code capture */
	priv->write_reg(priv, REG_TXERR, 0x0);
	priv->write_reg(priv, REG_RXERR, 0x0);
	priv->read_reg(priv, REG_ECC);

	/* leave reset mode */
	set_normal_mode(dev);
}