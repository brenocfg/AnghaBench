#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct TYPE_9__ {TYPE_1__ direct; } ;
struct TYPE_8__ {TYPE_4__ buf; } ;
struct mlx4_en_rx_ring {int size; int size_mask; int stride; int /*<<< orphan*/ * rx_info; scalar_t__ buf_size; TYPE_3__ wqres; int /*<<< orphan*/  hwtstamp_rx_filter; int /*<<< orphan*/  buf; scalar_t__ log_stride; scalar_t__ cons; scalar_t__ prod; } ;
struct mlx4_en_rx_alloc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_filter; } ;
struct mlx4_en_priv {TYPE_2__ hwtstamp_config; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int ENOMEM ; 
 int MLX4_EN_MAX_RX_FRAGS ; 
 int PAGE_SIZE ; 
 scalar_t__ TXBB_SIZE ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 scalar_t__ ffs (int) ; 
 int mlx4_alloc_hwq_res (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int) ; 
 int mlx4_en_map_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (int) ; 

int mlx4_en_create_rx_ring(struct mlx4_en_priv *priv,
			   struct mlx4_en_rx_ring *ring, u32 size, u16 stride)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	int err = -ENOMEM;
	int tmp;

	ring->prod = 0;
	ring->cons = 0;
	ring->size = size;
	ring->size_mask = size - 1;
	ring->stride = stride;
	ring->log_stride = ffs(ring->stride) - 1;
	ring->buf_size = ring->size * ring->stride + TXBB_SIZE;

	tmp = size * roundup_pow_of_two(MLX4_EN_MAX_RX_FRAGS *
					sizeof(struct mlx4_en_rx_alloc));
	ring->rx_info = vmalloc(tmp);
	if (!ring->rx_info) {
		en_err(priv, "Failed allocating rx_info ring\n");
		return -ENOMEM;
	}
	en_dbg(DRV, priv, "Allocated rx_info ring at addr:%p size:%d\n",
		 ring->rx_info, tmp);

	err = mlx4_alloc_hwq_res(mdev->dev, &ring->wqres,
				 ring->buf_size, 2 * PAGE_SIZE);
	if (err)
		goto err_ring;

	err = mlx4_en_map_buffer(&ring->wqres.buf);
	if (err) {
		en_err(priv, "Failed to map RX buffer\n");
		goto err_hwq;
	}
	ring->buf = ring->wqres.buf.direct.buf;

	ring->hwtstamp_rx_filter = priv->hwtstamp_config.rx_filter;

	return 0;

err_hwq:
	mlx4_free_hwq_res(mdev->dev, &ring->wqres, ring->buf_size);
err_ring:
	vfree(ring->rx_info);
	ring->rx_info = NULL;
	return err;
}