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
struct TYPE_2__ {int num_ports; } ;
struct mthca_dev {struct ib_mad_agent*** send_agent; TYPE_1__ limits; int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  sm_lock; } ;
struct ib_mad_agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  IB_QPT_SMI ; 
 scalar_t__ IS_ERR (struct ib_mad_agent*) ; 
 int PTR_ERR (struct ib_mad_agent*) ; 
 struct ib_mad_agent* ib_register_mad_agent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (struct ib_mad_agent*) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*,int) ; 
 int mthca_update_rate (struct mthca_dev*,int) ; 
 int /*<<< orphan*/  send_handler ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mthca_create_agents(struct mthca_dev *dev)
{
	struct ib_mad_agent *agent;
	int p, q;
	int ret;

	spin_lock_init(&dev->sm_lock);

	for (p = 0; p < dev->limits.num_ports; ++p)
		for (q = 0; q <= 1; ++q) {
			agent = ib_register_mad_agent(&dev->ib_dev, p + 1,
						      q ? IB_QPT_GSI : IB_QPT_SMI,
						      NULL, 0, send_handler,
						      NULL, NULL);
			if (IS_ERR(agent)) {
				ret = PTR_ERR(agent);
				goto err;
			}
			dev->send_agent[p][q] = agent;
		}


	for (p = 1; p <= dev->limits.num_ports; ++p) {
		ret = mthca_update_rate(dev, p);
		if (ret) {
			mthca_err(dev, "Failed to obtain port %d rate."
				  " aborting.\n", p);
			goto err;
		}
	}

	return 0;

err:
	for (p = 0; p < dev->limits.num_ports; ++p)
		for (q = 0; q <= 1; ++q)
			if (dev->send_agent[p][q])
				ib_unregister_mad_agent(dev->send_agent[p][q]);

	return ret;
}