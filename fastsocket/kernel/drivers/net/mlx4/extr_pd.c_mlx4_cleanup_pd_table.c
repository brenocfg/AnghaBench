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
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pd_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_bitmap_cleanup (int /*<<< orphan*/ *) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_cleanup_pd_table(struct mlx4_dev *dev)
{
	mlx4_bitmap_cleanup(&mlx4_priv(dev)->pd_bitmap);
}