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
struct mlx4_en_priv {TYPE_1__* ethtool_rules; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int MAX_NUM_OF_FS_RULES ; 

__attribute__((used)) static int mlx4_en_get_num_flows(struct mlx4_en_priv *priv)
{

	int i, res = 0;
	for (i = 0; i < MAX_NUM_OF_FS_RULES; i++) {
		if (priv->ethtool_rules[i].id)
			res++;
	}
	return res;

}