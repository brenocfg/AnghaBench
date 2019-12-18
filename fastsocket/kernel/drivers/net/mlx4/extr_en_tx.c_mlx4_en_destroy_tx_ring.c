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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct mlx4_en_tx_ring {int /*<<< orphan*/ * tx_info; int /*<<< orphan*/ * bounce_buf; int /*<<< orphan*/  buf_size; TYPE_1__ wqres; int /*<<< orphan*/  qp; int /*<<< orphan*/  bf; scalar_t__ bf_enabled; int /*<<< orphan*/  qpn; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_bf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_en_unmap_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_qp_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_qp_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void mlx4_en_destroy_tx_ring(struct mlx4_en_priv *priv,
			     struct mlx4_en_tx_ring *ring)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	en_dbg(DRV, priv, "Destroying tx ring, qpn: %d\n", ring->qpn);

	if (ring->bf_enabled)
		mlx4_bf_free(mdev->dev, &ring->bf);
	mlx4_qp_remove(mdev->dev, &ring->qp);
	mlx4_qp_free(mdev->dev, &ring->qp);
	mlx4_en_unmap_buffer(&ring->wqres.buf);
	mlx4_free_hwq_res(mdev->dev, &ring->wqres, ring->buf_size);
	kfree(ring->bounce_buf);
	ring->bounce_buf = NULL;
	vfree(ring->tx_info);
	ring->tx_info = NULL;
}