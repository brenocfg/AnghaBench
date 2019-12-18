#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_dev {int num_slaves; } ;
typedef  enum slave_port_gen_event { ____Placeholder_slave_port_gen_event } slave_port_gen_event ;

/* Variables and functions */
 int /*<<< orphan*/  set_and_calc_slave_port_state (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void set_all_slave_state(struct mlx4_dev *dev, u8 port, int event)
{
	int i;
	enum slave_port_gen_event gen_event;

	for (i = 0; i < dev->num_slaves; i++)
		set_and_calc_slave_port_state(dev, i, port, event, &gen_event);
}