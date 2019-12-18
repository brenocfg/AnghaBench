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
struct mlx4_en_rx_ring {int stride; int /*<<< orphan*/  page_alloc; struct mlx4_en_rx_alloc* rx_info; struct mlx4_en_rx_desc* buf; } ;
struct mlx4_en_rx_desc {int dummy; } ;
struct mlx4_en_rx_alloc {int dummy; } ;
struct mlx4_en_priv {int log_rx_info; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int mlx4_en_alloc_frags (struct mlx4_en_priv*,struct mlx4_en_rx_desc*,struct mlx4_en_rx_alloc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_prepare_rx_desc(struct mlx4_en_priv *priv,
				   struct mlx4_en_rx_ring *ring, int index,
				   gfp_t gfp)
{
	struct mlx4_en_rx_desc *rx_desc = ring->buf + (index * ring->stride);
	struct mlx4_en_rx_alloc *frags = ring->rx_info +
					(index << priv->log_rx_info);

	return mlx4_en_alloc_frags(priv, rx_desc, frags, ring->page_alloc, gfp);
}