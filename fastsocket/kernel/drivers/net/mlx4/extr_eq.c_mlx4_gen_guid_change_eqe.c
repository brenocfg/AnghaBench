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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ port_mgmt_change; } ;
struct mlx4_eqe {TYPE_2__ event; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct mlx4_dev {int num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DEV_PMC_SUBTYPE_GUID_INFO ; 
 int /*<<< orphan*/  MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT ; 
 int /*<<< orphan*/  memset (struct mlx4_eqe*,int /*<<< orphan*/ ,int) ; 
 int mlx4_GEN_EQE (struct mlx4_dev*,int,struct mlx4_eqe*) ; 

int mlx4_gen_guid_change_eqe(struct mlx4_dev *dev, int slave, u8 port)
{
	struct mlx4_eqe eqe;

	/*don't send if we don't have the that slave */
	if (dev->num_vfs < slave)
		return 0;
	memset(&eqe, 0, sizeof eqe);

	eqe.type = MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT;
	eqe.subtype = MLX4_DEV_PMC_SUBTYPE_GUID_INFO;
	eqe.event.port_mgmt_change.port = port;

	return mlx4_GEN_EQE(dev, slave, &eqe);
}