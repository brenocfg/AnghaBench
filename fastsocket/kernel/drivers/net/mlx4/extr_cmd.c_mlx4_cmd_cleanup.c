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
struct TYPE_6__ {int /*<<< orphan*/ * vhcr; int /*<<< orphan*/  vhcr_dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  hcr; int /*<<< orphan*/  pool; } ;
struct mlx4_priv {TYPE_3__ mfunc; TYPE_1__ cmd; } ;
struct mlx4_dev {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_slave (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  pci_pool_destroy (int /*<<< orphan*/ ) ; 

void mlx4_cmd_cleanup(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	pci_pool_destroy(priv->cmd.pool);

	if (!mlx4_is_slave(dev))
		iounmap(priv->cmd.hcr);
	if (mlx4_is_mfunc(dev))
		dma_free_coherent(&(dev->pdev->dev), PAGE_SIZE,
				  priv->mfunc.vhcr, priv->mfunc.vhcr_dma);
	priv->mfunc.vhcr = NULL;
}