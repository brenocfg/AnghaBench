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
struct mlx4_sense {scalar_t__* sense_allowed; scalar_t__* do_sense_port; } ;
struct TYPE_3__ {int num_ports; scalar_t__* possible_type; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  enum mlx4_port_type { ____Placeholder_mlx4_port_type } mlx4_port_type ;
struct TYPE_4__ {struct mlx4_sense sense; } ;

/* Variables and functions */
 scalar_t__ MLX4_PORT_TYPE_AUTO ; 
 int mlx4_SENSE_PORT (struct mlx4_dev*,int,int*) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_do_sense_ports(struct mlx4_dev *dev,
			 enum mlx4_port_type *stype,
			 enum mlx4_port_type *defaults)
{
	struct mlx4_sense *sense = &mlx4_priv(dev)->sense;
	int err;
	int i;

	for (i = 1; i <= dev->caps.num_ports; i++) {
		stype[i - 1] = 0;
		if (sense->do_sense_port[i] && sense->sense_allowed[i] &&
		    dev->caps.possible_type[i] == MLX4_PORT_TYPE_AUTO) {
			err = mlx4_SENSE_PORT(dev, i, &stype[i - 1]);
			if (err)
				stype[i - 1] = defaults[i - 1];
		} else
			stype[i - 1] = defaults[i - 1];
	}

	/*
	 * If sensed nothing, remain in current configuration.
	 */
	for (i = 0; i < dev->caps.num_ports; i++)
		stype[i] = stype[i] ? stype[i] : defaults[i];

}