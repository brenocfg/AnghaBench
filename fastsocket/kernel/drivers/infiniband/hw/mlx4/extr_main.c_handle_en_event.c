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
struct TYPE_2__ {int /*<<< orphan*/ ** netdevs; } ;
struct mlx4_ib_dev {TYPE_1__ iboe; } ;

/* Variables and functions */
#define  NETDEV_CHANGEADDR 130 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  update_ipv6_gids (struct mlx4_ib_dev*,int,int) ; 

__attribute__((used)) static void handle_en_event(struct mlx4_ib_dev *dev, int port, unsigned long event)
{
	switch (event) {
	case NETDEV_UP:
	case NETDEV_CHANGEADDR:
		update_ipv6_gids(dev, port, 0);
		break;

	case NETDEV_DOWN:
		update_ipv6_gids(dev, port, 1);
		dev->iboe.netdevs[port - 1] = NULL;
	}
}