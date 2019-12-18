#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {TYPE_2__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
struct mlx4_en_cq {int /*<<< orphan*/ * buf; int /*<<< orphan*/  buf_size; scalar_t__ vector; TYPE_4__ wqres; } ;
struct TYPE_5__ {scalar_t__ comp_pool; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_en_unmap_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_release_eq (TYPE_2__*,scalar_t__) ; 

void mlx4_en_destroy_cq(struct mlx4_en_priv *priv, struct mlx4_en_cq *cq)
{
	struct mlx4_en_dev *mdev = priv->mdev;

	mlx4_en_unmap_buffer(&cq->wqres.buf);
	mlx4_free_hwq_res(mdev->dev, &cq->wqres, cq->buf_size);
	if (priv->mdev->dev->caps.comp_pool && cq->vector)
		mlx4_release_eq(priv->mdev->dev, cq->vector);
	cq->vector = 0;
	cq->buf_size = 0;
	cq->buf = NULL;
}