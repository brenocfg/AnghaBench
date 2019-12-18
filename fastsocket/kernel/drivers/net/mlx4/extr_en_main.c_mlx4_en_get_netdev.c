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
typedef  size_t u8 ;
struct mlx4_en_dev {void** pndev; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void *mlx4_en_get_netdev(struct mlx4_dev *dev, void *ctx, u8 port)
{
	struct mlx4_en_dev *endev = ctx;

	return endev->pndev[port];
}