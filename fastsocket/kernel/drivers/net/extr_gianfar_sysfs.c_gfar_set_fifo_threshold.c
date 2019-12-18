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
typedef  unsigned int u32 ;
struct gfar_private {unsigned int fifo_threshold; int /*<<< orphan*/  txlock; TYPE_1__* regs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  fifo_tx_thr; } ;

/* Variables and functions */
 unsigned int FIFO_TX_THR_MASK ; 
 unsigned int GFAR_MAX_FIFO_THRESHOLD ; 
 unsigned int gfar_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfar_write (int /*<<< orphan*/ *,unsigned int) ; 
 struct gfar_private* netdev_priv (int /*<<< orphan*/ ) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t gfar_set_fifo_threshold(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	struct gfar_private *priv = netdev_priv(to_net_dev(dev));
	unsigned int length = simple_strtoul(buf, NULL, 0);
	u32 temp;
	unsigned long flags;

	if (length > GFAR_MAX_FIFO_THRESHOLD)
		return count;

	spin_lock_irqsave(&priv->txlock, flags);

	priv->fifo_threshold = length;

	temp = gfar_read(&priv->regs->fifo_tx_thr);
	temp &= ~FIFO_TX_THR_MASK;
	temp |= length;
	gfar_write(&priv->regs->fifo_tx_thr, temp);

	spin_unlock_irqrestore(&priv->txlock, flags);

	return count;
}