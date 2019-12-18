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
typedef  size_t u8 ;
typedef  int u64 ;
struct mlx4_mac_table {int* refs; scalar_t__ total; scalar_t__ max; int /*<<< orphan*/  mutex; scalar_t__* entries; } ;
struct mlx4_port_info {struct mlx4_mac_table mac_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_port_info* port; } ;

/* Variables and functions */
 int ENOSPC ; 
 int MLX4_MAC_MASK ; 
 int MLX4_MAC_VALID ; 
 int MLX4_MAX_MAC_NUM ; 
 int be64_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be64 (int) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int,...) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,unsigned long long) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_set_port_mac_table (struct mlx4_dev*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __mlx4_register_mac(struct mlx4_dev *dev, u8 port, u64 mac)
{
	struct mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	struct mlx4_mac_table *table = &info->mac_table;
	int i, err = 0;
	int free = -1;

	mlx4_dbg(dev, "Registering MAC: 0x%llx for port %d\n",
		 (unsigned long long) mac, port);

	mutex_lock(&table->mutex);
	for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
		if (free < 0 && !table->entries[i]) {
			free = i;
			continue;
		}

		if (mac == (MLX4_MAC_MASK & be64_to_cpu(table->entries[i]))) {
			/* MAC already registered, increment ref count */
			err = i;
			++table->refs[i];
			goto out;
		}
	}

	mlx4_dbg(dev, "Free MAC index is %d\n", free);

	if (table->total == table->max) {
		/* No free mac entries */
		err = -ENOSPC;
		goto out;
	}

	/* Register new MAC */
	table->entries[free] = cpu_to_be64(mac | MLX4_MAC_VALID);

	err = mlx4_set_port_mac_table(dev, port, table->entries);
	if (unlikely(err)) {
		mlx4_err(dev, "Failed adding MAC: 0x%llx\n",
			 (unsigned long long) mac);
		table->entries[free] = 0;
		goto out;
	}
	table->refs[free] = 1;
	err = free;
	++table->total;
out:
	mutex_unlock(&table->mutex);
	return err;
}