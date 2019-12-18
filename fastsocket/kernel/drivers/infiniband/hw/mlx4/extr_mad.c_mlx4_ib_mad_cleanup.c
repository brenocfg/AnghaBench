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
struct mlx4_ib_dev {int num_ports; scalar_t__* sm_ah; struct ib_mad_agent*** send_agent; } ;
struct ib_mad_agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_ah (scalar_t__) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (struct ib_mad_agent*) ; 

void mlx4_ib_mad_cleanup(struct mlx4_ib_dev *dev)
{
	struct ib_mad_agent *agent;
	int p, q;

	for (p = 0; p < dev->num_ports; ++p) {
		for (q = 0; q <= 1; ++q) {
			agent = dev->send_agent[p][q];
			if (agent) {
				dev->send_agent[p][q] = NULL;
				ib_unregister_mad_agent(agent);
			}
		}

		if (dev->sm_ah[p])
			ib_destroy_ah(dev->sm_ah[p]);
	}
}