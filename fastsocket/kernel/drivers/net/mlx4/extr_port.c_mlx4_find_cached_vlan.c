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
struct mlx4_vlan_table {int /*<<< orphan*/ * entries; scalar_t__* refs; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {struct mlx4_vlan_table vlan_table; } ;

/* Variables and functions */
 int ENOENT ; 
 int MLX4_MAX_VLAN_NUM ; 
 int MLX4_VLAN_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_find_cached_vlan(struct mlx4_dev *dev, u8 port, u16 vid, int *idx)
{
	struct mlx4_vlan_table *table = &mlx4_priv(dev)->port[port].vlan_table;
	int i;

	for (i = 0; i < MLX4_MAX_VLAN_NUM; ++i) {
		if (table->refs[i] &&
		    (vid == (MLX4_VLAN_MASK &
			      be32_to_cpu(table->entries[i])))) {
			/* VLAN already registered, increase reference count */
			*idx = i;
			return 0;
		}
	}

	return -ENOENT;
}