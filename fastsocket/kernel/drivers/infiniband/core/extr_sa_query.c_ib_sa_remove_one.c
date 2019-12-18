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
struct ib_sa_device {int end_port; int start_port; TYPE_2__* port; int /*<<< orphan*/  event_handler; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sm_ah; int /*<<< orphan*/  agent; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_sm_ah ; 
 struct ib_sa_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_wq ; 
 int /*<<< orphan*/  kfree (struct ib_sa_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int) ; 
 int /*<<< orphan*/  sa_client ; 

__attribute__((used)) static void ib_sa_remove_one(struct ib_device *device)
{
	struct ib_sa_device *sa_dev = ib_get_client_data(device, &sa_client);
	int i;

	if (!sa_dev)
		return;

	ib_unregister_event_handler(&sa_dev->event_handler);

	flush_workqueue(ib_wq);

	for (i = 0; i <= sa_dev->end_port - sa_dev->start_port; ++i) {
		if (rdma_port_get_link_layer(device, i + 1) == IB_LINK_LAYER_INFINIBAND) {
			ib_unregister_mad_agent(sa_dev->port[i].agent);
			if (sa_dev->port[i].sm_ah)
				kref_put(&sa_dev->port[i].sm_ah->ref, free_sm_ah);
		}

	}

	kfree(sa_dev);
}