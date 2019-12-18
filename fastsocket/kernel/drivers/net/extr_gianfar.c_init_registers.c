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
struct rmon_mib {int dummy; } ;
struct net_device {int dummy; } ;
struct gfar_private {int device_flags; int rx_buffer_size; TYPE_1__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  cam2; int /*<<< orphan*/  cam1; } ;
struct TYPE_3__ {int /*<<< orphan*/  minflr; int /*<<< orphan*/  mrblr; TYPE_2__ rmon; int /*<<< orphan*/  gaddr7; int /*<<< orphan*/  gaddr6; int /*<<< orphan*/  gaddr5; int /*<<< orphan*/  gaddr4; int /*<<< orphan*/  gaddr3; int /*<<< orphan*/  gaddr2; int /*<<< orphan*/  gaddr1; int /*<<< orphan*/  gaddr0; int /*<<< orphan*/  igaddr7; int /*<<< orphan*/  igaddr6; int /*<<< orphan*/  igaddr5; int /*<<< orphan*/  igaddr4; int /*<<< orphan*/  igaddr3; int /*<<< orphan*/  igaddr2; int /*<<< orphan*/  igaddr1; int /*<<< orphan*/  igaddr0; int /*<<< orphan*/  imask; int /*<<< orphan*/  ievent; } ;

/* Variables and functions */
 int FSL_GIANFAR_DEV_HAS_RMON ; 
 int IEVENT_INIT_CLEAR ; 
 int IMASK_INIT_CLEAR ; 
 int MINFLR_INIT_SETTINGS ; 
 int /*<<< orphan*/  gfar_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset_io (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void init_registers(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);

	/* Clear IEVENT */
	gfar_write(&priv->regs->ievent, IEVENT_INIT_CLEAR);

	/* Initialize IMASK */
	gfar_write(&priv->regs->imask, IMASK_INIT_CLEAR);

	/* Init hash registers to zero */
	gfar_write(&priv->regs->igaddr0, 0);
	gfar_write(&priv->regs->igaddr1, 0);
	gfar_write(&priv->regs->igaddr2, 0);
	gfar_write(&priv->regs->igaddr3, 0);
	gfar_write(&priv->regs->igaddr4, 0);
	gfar_write(&priv->regs->igaddr5, 0);
	gfar_write(&priv->regs->igaddr6, 0);
	gfar_write(&priv->regs->igaddr7, 0);

	gfar_write(&priv->regs->gaddr0, 0);
	gfar_write(&priv->regs->gaddr1, 0);
	gfar_write(&priv->regs->gaddr2, 0);
	gfar_write(&priv->regs->gaddr3, 0);
	gfar_write(&priv->regs->gaddr4, 0);
	gfar_write(&priv->regs->gaddr5, 0);
	gfar_write(&priv->regs->gaddr6, 0);
	gfar_write(&priv->regs->gaddr7, 0);

	/* Zero out the rmon mib registers if it has them */
	if (priv->device_flags & FSL_GIANFAR_DEV_HAS_RMON) {
		memset_io(&(priv->regs->rmon), 0, sizeof (struct rmon_mib));

		/* Mask off the CAM interrupts */
		gfar_write(&priv->regs->rmon.cam1, 0xffffffff);
		gfar_write(&priv->regs->rmon.cam2, 0xffffffff);
	}

	/* Initialize the max receive buffer length */
	gfar_write(&priv->regs->mrblr, priv->rx_buffer_size);

	/* Initialize the Minimum Frame Length Register */
	gfar_write(&priv->regs->minflr, MINFLR_INIT_SETTINGS);
}