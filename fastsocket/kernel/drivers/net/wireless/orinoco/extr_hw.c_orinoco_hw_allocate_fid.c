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
struct hermes {TYPE_1__* ops; } ;
struct orinoco_private {int /*<<< orphan*/  txfid; int /*<<< orphan*/  nicbuf_size; struct hermes hw; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* allocate ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TX_NICBUF_SIZE_BUG ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*) ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int orinoco_hw_allocate_fid(struct orinoco_private *priv)
{
	struct device *dev = priv->dev;
	struct hermes *hw = &priv->hw;
	int err;

	err = hw->ops->allocate(hw, priv->nicbuf_size, &priv->txfid);
	if (err == -EIO && priv->nicbuf_size > TX_NICBUF_SIZE_BUG) {
		/* Try workaround for old Symbol firmware bug */
		priv->nicbuf_size = TX_NICBUF_SIZE_BUG;
		err = hw->ops->allocate(hw, priv->nicbuf_size, &priv->txfid);

		dev_warn(dev, "Firmware ALLOC bug detected "
			 "(old Symbol firmware?). Work around %s\n",
			 err ? "failed!" : "ok.");
	}

	return err;
}