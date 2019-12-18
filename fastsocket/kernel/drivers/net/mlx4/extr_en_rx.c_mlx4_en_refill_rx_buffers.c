#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mlx4_en_rx_ring {int prod; int size_mask; int cons; scalar_t__ actual_size; } ;
struct mlx4_en_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ mlx4_en_prepare_rx_desc (struct mlx4_en_priv*,struct mlx4_en_rx_ring*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_en_refill_rx_buffers(struct mlx4_en_priv *priv,
				     struct mlx4_en_rx_ring *ring)
{
	int index = ring->prod & ring->size_mask;

	while ((u32) (ring->prod - ring->cons) < ring->actual_size) {
		if (mlx4_en_prepare_rx_desc(priv, ring, index, GFP_ATOMIC))
			break;
		ring->prod++;
		index = ring->prod & ring->size_mask;
	}
}