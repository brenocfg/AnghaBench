#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int*** virt2phys_pkey; int** phys_pkey_cache; } ;
struct mlx4_ib_dev {TYPE_3__ pkeys; TYPE_4__* dev; } ;
struct TYPE_8__ {int* pkey_phys_table_len; } ;
struct TYPE_7__ {int num_ports; } ;
struct TYPE_10__ {int num_vfs; TYPE_2__ phys_caps; TYPE_1__ caps; } ;

/* Variables and functions */
 scalar_t__ mlx4_is_master (TYPE_4__*) ; 
 int mlx4_master_func_num (TYPE_4__*) ; 
 int /*<<< orphan*/  mlx4_sync_pkey_table (TYPE_4__*,int,int,int,int) ; 

__attribute__((used)) static void init_pkeys(struct mlx4_ib_dev *ibdev)
{
	int port;
	int slave;
	int i;

	if (mlx4_is_master(ibdev->dev)) {
		for (slave = 0; slave <= ibdev->dev->num_vfs; ++slave) {
			for (port = 1; port <= ibdev->dev->caps.num_ports; ++port) {
				for (i = 0;
				     i < ibdev->dev->phys_caps.pkey_phys_table_len[port];
				     ++i) {
					ibdev->pkeys.virt2phys_pkey[slave][port - 1][i] =
					/* master has the identity virt2phys pkey mapping */
						(slave == mlx4_master_func_num(ibdev->dev) || !i) ? i :
							ibdev->dev->phys_caps.pkey_phys_table_len[port] - 1;
					mlx4_sync_pkey_table(ibdev->dev, slave, port, i,
							     ibdev->pkeys.virt2phys_pkey[slave][port - 1][i]);
				}
			}
		}
		/* initialize pkey cache */
		for (port = 1; port <= ibdev->dev->caps.num_ports; ++port) {
			for (i = 0;
			     i < ibdev->dev->phys_caps.pkey_phys_table_len[port];
			     ++i)
				ibdev->pkeys.phys_pkey_cache[port-1][i] =
					(i) ? 0 : 0xFFFF;
		}
	}
}