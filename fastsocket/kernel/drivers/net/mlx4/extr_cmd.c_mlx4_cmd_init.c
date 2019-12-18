#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int toggle; int /*<<< orphan*/ * hcr; int /*<<< orphan*/  pool; scalar_t__ use_events; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/  slave_cmd_mutex; int /*<<< orphan*/  hcr_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/ * vhcr; int /*<<< orphan*/  vhcr_dma; } ;
struct mlx4_priv {TYPE_2__ cmd; TYPE_1__ mfunc; } ;
struct mlx4_dev {TYPE_3__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MLX4_HCR_BASE ; 
 int /*<<< orphan*/  MLX4_HCR_SIZE ; 
 int /*<<< orphan*/  MLX4_MAILBOX_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_slave (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_create (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

int mlx4_cmd_init(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);

	mutex_init(&priv->cmd.hcr_mutex);
	mutex_init(&priv->cmd.slave_cmd_mutex);
	sema_init(&priv->cmd.poll_sem, 1);
	priv->cmd.use_events = 0;
	priv->cmd.toggle     = 1;

	priv->cmd.hcr = NULL;
	priv->mfunc.vhcr = NULL;

	if (!mlx4_is_slave(dev)) {
		priv->cmd.hcr = ioremap(pci_resource_start(dev->pdev, 0) +
					MLX4_HCR_BASE, MLX4_HCR_SIZE);
		if (!priv->cmd.hcr) {
			mlx4_err(dev, "Couldn't map command register.\n");
			return -ENOMEM;
		}
	}

	if (mlx4_is_mfunc(dev)) {
		priv->mfunc.vhcr = dma_alloc_coherent(&(dev->pdev->dev), PAGE_SIZE,
						      &priv->mfunc.vhcr_dma,
						      GFP_KERNEL);
		if (!priv->mfunc.vhcr) {
			mlx4_err(dev, "Couldn't allocate VHCR.\n");
			goto err_hcr;
		}
	}

	priv->cmd.pool = pci_pool_create("mlx4_cmd", dev->pdev,
					 MLX4_MAILBOX_SIZE,
					 MLX4_MAILBOX_SIZE, 0);
	if (!priv->cmd.pool)
		goto err_vhcr;

	return 0;

err_vhcr:
	if (mlx4_is_mfunc(dev))
		dma_free_coherent(&(dev->pdev->dev), PAGE_SIZE,
				  priv->mfunc.vhcr, priv->mfunc.vhcr_dma);
	priv->mfunc.vhcr = NULL;

err_hcr:
	if (!mlx4_is_slave(dev))
		iounmap(priv->cmd.hcr);
	return -ENOMEM;
}