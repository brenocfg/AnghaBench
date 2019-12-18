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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * demux; int /*<<< orphan*/  is_going_down; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; TYPE_1__ sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_CLIENT_REREGISTER ; 
 int /*<<< orphan*/  MLX4_EQ_PORT_INFO_CLIENT_REREG_MASK ; 
 int /*<<< orphan*/  mlx4_gen_slaves_port_mgt_ev (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_ib_dispatch_event (struct mlx4_ib_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_ib_invalidate_all_guid_record (struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx4_ib_mcg_port_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_client_rereg_event(struct mlx4_ib_dev *dev, u8 port_num)
{
	/* re-configure the alias-guid and mcg's */
	if (mlx4_is_master(dev->dev)) {
		mlx4_ib_invalidate_all_guid_record(dev, port_num);

		if (!dev->sriov.is_going_down) {
			mlx4_ib_mcg_port_cleanup(&dev->sriov.demux[port_num - 1], 0);
			mlx4_gen_slaves_port_mgt_ev(dev->dev, port_num,
						    MLX4_EQ_PORT_INFO_CLIENT_REREG_MASK);
		}
	}
	mlx4_ib_dispatch_event(dev, port_num, IB_EVENT_CLIENT_REREGISTER);
}