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
struct mlx4_en_rx_ring {int actual_size; int /*<<< orphan*/  prod; } ;
struct mlx4_en_priv {int rx_ring_num; struct mlx4_en_rx_ring* rx_ring; TYPE_1__* prof; } ;
struct TYPE_2__ {int rx_ring_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX4_EN_MIN_RX_SIZE ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*,int,int) ; 
 int /*<<< orphan*/  mlx4_en_free_rx_desc (struct mlx4_en_priv*,struct mlx4_en_rx_ring*,int) ; 
 scalar_t__ mlx4_en_prepare_rx_desc (struct mlx4_en_priv*,struct mlx4_en_rx_ring*,int,int /*<<< orphan*/ ) ; 
 int rounddown_pow_of_two (int) ; 

__attribute__((used)) static int mlx4_en_fill_rx_buffers(struct mlx4_en_priv *priv)
{
	struct mlx4_en_rx_ring *ring;
	int ring_ind;
	int buf_ind;
	int new_size;

	for (buf_ind = 0; buf_ind < priv->prof->rx_ring_size; buf_ind++) {
		for (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) {
			ring = &priv->rx_ring[ring_ind];

			if (mlx4_en_prepare_rx_desc(priv, ring,
						    ring->actual_size,
						    GFP_KERNEL)) {
				if (ring->actual_size < MLX4_EN_MIN_RX_SIZE) {
					en_err(priv, "Failed to allocate "
						     "enough rx buffers\n");
					return -ENOMEM;
				} else {
					new_size = rounddown_pow_of_two(ring->actual_size);
					en_warn(priv, "Only %d buffers allocated "
						      "reducing ring size to %d",
						ring->actual_size, new_size);
					goto reduce_rings;
				}
			}
			ring->actual_size++;
			ring->prod++;
		}
	}
	return 0;

reduce_rings:
	for (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) {
		ring = &priv->rx_ring[ring_ind];
		while (ring->actual_size > new_size) {
			ring->actual_size--;
			ring->prod--;
			mlx4_en_free_rx_desc(priv, ring, ring->actual_size);
		}
	}

	return 0;
}