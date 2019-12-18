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
typedef  size_t u8 ;
typedef  int u16 ;
struct mlx4_vlan_table {scalar_t__ total; scalar_t__ max; int* refs; int /*<<< orphan*/  mutex; scalar_t__* entries; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {struct mlx4_vlan_table vlan_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int MLX4_MAX_VLAN_NUM ; 
 int MLX4_VLAN_MASK ; 
 int MLX4_VLAN_REGULAR ; 
 int MLX4_VLAN_VALID ; 
 int be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_set_port_vlan_table (struct mlx4_dev*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __mlx4_register_vlan(struct mlx4_dev *dev, u8 port, u16 vlan,
				int *index)
{
	struct mlx4_vlan_table *table = &mlx4_priv(dev)->port[port].vlan_table;
	int i, err = 0;
	int free = -1;

	mutex_lock(&table->mutex);

	if (table->total == table->max) {
		/* No free vlan entries */
		err = -ENOSPC;
		goto out;
	}

	for (i = MLX4_VLAN_REGULAR; i < MLX4_MAX_VLAN_NUM; i++) {
		if (free < 0 && (table->refs[i] == 0)) {
			free = i;
			continue;
		}

		if (table->refs[i] &&
		    (vlan == (MLX4_VLAN_MASK &
			      be32_to_cpu(table->entries[i])))) {
			/* Vlan already registered, increase references count */
			*index = i;
			++table->refs[i];
			goto out;
		}
	}

	if (free < 0) {
		err = -ENOMEM;
		goto out;
	}

	/* Register new VLAN */
	table->refs[free] = 1;
	table->entries[free] = cpu_to_be32(vlan | MLX4_VLAN_VALID);

	err = mlx4_set_port_vlan_table(dev, port, table->entries);
	if (unlikely(err)) {
		mlx4_warn(dev, "Failed adding vlan: %u\n", vlan);
		table->refs[free] = 0;
		table->entries[free] = 0;
		goto out;
	}

	*index = free;
	++table->total;
out:
	mutex_unlock(&table->mutex);
	return err;
}