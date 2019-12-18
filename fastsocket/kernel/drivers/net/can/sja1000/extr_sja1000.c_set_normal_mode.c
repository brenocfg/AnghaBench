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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct sja1000_priv {unsigned char (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ,int) ;TYPE_1__ can; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int IRQ_ALL ; 
 unsigned char MOD_RM ; 
 int /*<<< orphan*/  REG_IER ; 
 int /*<<< orphan*/  REG_MOD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 unsigned char stub1 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 unsigned char stub4 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void set_normal_mode(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);
	unsigned char status = priv->read_reg(priv, REG_MOD);
	int i;

	for (i = 0; i < 100; i++) {
		/* check reset bit */
		if ((status & MOD_RM) == 0) {
			priv->can.state = CAN_STATE_ERROR_ACTIVE;
			/* enable all interrupts */
			priv->write_reg(priv, REG_IER, IRQ_ALL);
			return;
		}

		/* set chip to normal mode */
		priv->write_reg(priv, REG_MOD, 0x00);
		udelay(10);
		status = priv->read_reg(priv, REG_MOD);
	}

	dev_err(dev->dev.parent, "setting SJA1000 into normal mode failed!\n");
}