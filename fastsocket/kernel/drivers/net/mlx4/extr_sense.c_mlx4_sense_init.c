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
struct mlx4_sense {int* do_sense_port; int /*<<< orphan*/  sense_poll; struct mlx4_dev* dev; } ;
struct mlx4_priv {struct mlx4_sense sense; } ;
struct TYPE_2__ {int num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK_DEFERRABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_sense_port ; 

void  mlx4_sense_init(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_sense *sense = &priv->sense;
	int port;

	sense->dev = dev;
	for (port = 1; port <= dev->caps.num_ports; port++)
		sense->do_sense_port[port] = 1;

	INIT_DELAYED_WORK_DEFERRABLE(&sense->sense_poll, mlx4_sense_port);
}