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
struct mlx4_en_rx_ring {struct mlx4_en_rx_alloc* rx_info; } ;
struct mlx4_en_rx_alloc {int dummy; } ;
struct mlx4_en_priv {int log_rx_info; int num_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int) ; 
 int /*<<< orphan*/  mlx4_en_free_frag (struct mlx4_en_priv*,struct mlx4_en_rx_alloc*,int) ; 

__attribute__((used)) static void mlx4_en_free_rx_desc(struct mlx4_en_priv *priv,
				 struct mlx4_en_rx_ring *ring,
				 int index)
{
	struct mlx4_en_rx_alloc *frags;
	int nr;

	frags = ring->rx_info + (index << priv->log_rx_info);
	for (nr = 0; nr < priv->num_frags; nr++) {
		en_dbg(DRV, priv, "Freeing fragment:%d\n", nr);
		mlx4_en_free_frag(priv, frags, nr);
	}
}