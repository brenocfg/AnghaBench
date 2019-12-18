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
typedef  int u32 ;
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct ixgbe_fcoe_ddp {int len; int /*<<< orphan*/ * pool; int /*<<< orphan*/  udp; int /*<<< orphan*/  udl; int /*<<< orphan*/  sgc; scalar_t__ sgl; scalar_t__ err; } ;
struct ixgbe_fcoe {int /*<<< orphan*/  lock; struct ixgbe_fcoe_ddp* ddp; } ;
struct ixgbe_adapter {TYPE_1__* pdev; int /*<<< orphan*/  hw; struct ixgbe_fcoe fcoe; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IXGBE_FCBUFF ; 
 int IXGBE_FCBUFF_VALID ; 
 int /*<<< orphan*/  IXGBE_FCDMARW ; 
 size_t IXGBE_FCDMARW_RE ; 
 size_t IXGBE_FCDMARW_WE ; 
 int /*<<< orphan*/  IXGBE_FCFLT ; 
 int /*<<< orphan*/  IXGBE_FCFLTRW ; 
 size_t IXGBE_FCFLTRW_WE ; 
 size_t IXGBE_FCOE_DDP_MAX ; 
 int IXGBE_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_fcoe_clear_ddp (struct ixgbe_fcoe_ddp*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ixgbe_fcoe_ddp_put(struct net_device *netdev, u16 xid)
{
	int len = 0;
	struct ixgbe_fcoe *fcoe;
	struct ixgbe_adapter *adapter;
	struct ixgbe_fcoe_ddp *ddp;
	u32 fcbuff;

	if (!netdev)
		goto out_ddp_put;

	if (xid >= IXGBE_FCOE_DDP_MAX)
		goto out_ddp_put;

	adapter = netdev_priv(netdev);
	fcoe = &adapter->fcoe;
	ddp = &fcoe->ddp[xid];
	if (!ddp->udl)
		goto out_ddp_put;

	len = ddp->len;
	/* if there an error, force to invalidate ddp context */
	if (ddp->err) {
		spin_lock_bh(&fcoe->lock);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCFLT, 0);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCFLTRW,
				(xid | IXGBE_FCFLTRW_WE));
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCBUFF, 0);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCDMARW,
				(xid | IXGBE_FCDMARW_WE));

		/* guaranteed to be invalidated after 100us */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_FCDMARW,
				(xid | IXGBE_FCDMARW_RE));
		fcbuff = IXGBE_READ_REG(&adapter->hw, IXGBE_FCBUFF);
		spin_unlock_bh(&fcoe->lock);
		if (fcbuff & IXGBE_FCBUFF_VALID)
			udelay(100);
	}
	if (ddp->sgl)
		dma_unmap_sg(&adapter->pdev->dev, ddp->sgl, ddp->sgc,
			     DMA_FROM_DEVICE);
	if (ddp->pool) {
		dma_pool_free(ddp->pool, ddp->udl, ddp->udp);
		ddp->pool = NULL;
	}

	ixgbe_fcoe_clear_ddp(ddp);

out_ddp_put:
	return len;
}