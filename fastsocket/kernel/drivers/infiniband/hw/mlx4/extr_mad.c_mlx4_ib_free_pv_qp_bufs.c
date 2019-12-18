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
struct mlx4_tunnel_mad {int dummy; } ;
struct mlx4_rcv_tunnel_mad {int dummy; } ;
struct mlx4_mad_snd_buf {int dummy; } ;
struct mlx4_mad_rcv_buf {int dummy; } ;
struct mlx4_ib_demux_pv_qp {TYPE_2__* ring; TYPE_2__* tx_ring; } ;
struct mlx4_ib_demux_pv_ctx {int /*<<< orphan*/  ib_dev; struct mlx4_ib_demux_pv_qp* qp; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_3__ {TYPE_2__* addr; int /*<<< orphan*/  map; } ;
struct TYPE_4__ {scalar_t__ ah; TYPE_1__ buf; struct TYPE_4__* addr; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int IB_QPT_GSI ; 
 int MLX4_NUM_TUNNEL_BUFS ; 
 int /*<<< orphan*/  ib_destroy_ah (scalar_t__) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void mlx4_ib_free_pv_qp_bufs(struct mlx4_ib_demux_pv_ctx *ctx,
				     enum ib_qp_type qp_type, int is_tun)
{
	int i;
	struct mlx4_ib_demux_pv_qp *tun_qp;
	int rx_buf_size, tx_buf_size;

	if (qp_type > IB_QPT_GSI)
		return;

	tun_qp = &ctx->qp[qp_type];
	if (is_tun) {
		rx_buf_size = sizeof (struct mlx4_tunnel_mad);
		tx_buf_size = sizeof (struct mlx4_rcv_tunnel_mad);
	} else {
		rx_buf_size = sizeof (struct mlx4_mad_rcv_buf);
		tx_buf_size = sizeof (struct mlx4_mad_snd_buf);
	}


	for (i = 0; i < MLX4_NUM_TUNNEL_BUFS; i++) {
		ib_dma_unmap_single(ctx->ib_dev, tun_qp->ring[i].map,
				    rx_buf_size, DMA_FROM_DEVICE);
		kfree(tun_qp->ring[i].addr);
	}

	for (i = 0; i < MLX4_NUM_TUNNEL_BUFS; i++) {
		ib_dma_unmap_single(ctx->ib_dev, tun_qp->tx_ring[i].buf.map,
				    tx_buf_size, DMA_TO_DEVICE);
		kfree(tun_qp->tx_ring[i].buf.addr);
		if (tun_qp->tx_ring[i].ah)
			ib_destroy_ah(tun_qp->tx_ring[i].ah);
	}
	kfree(tun_qp->tx_ring);
	kfree(tun_qp->ring);
}