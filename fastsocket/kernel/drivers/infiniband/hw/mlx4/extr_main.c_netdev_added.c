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
struct mlx4_ib_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_ipv6_gids (struct mlx4_ib_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netdev_added(struct mlx4_ib_dev *dev, int port)
{
	update_ipv6_gids(dev, port, 0);
}