#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_umad_port {int dummy; } ;
struct ib_umad_device {int start_port; int end_port; int /*<<< orphan*/  ref; TYPE_1__* port; } ;
struct ib_device {scalar_t__ node_type; int phys_port_cnt; } ;
struct TYPE_3__ {struct ib_umad_device* umad_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 scalar_t__ RDMA_TRANSPORT_IB ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct ib_umad_device*) ; 
 scalar_t__ ib_umad_init_port (struct ib_device*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ib_umad_kill_port (TYPE_1__*) ; 
 int /*<<< orphan*/  ib_umad_release_dev ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_umad_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_node_get_transport (scalar_t__) ; 
 int /*<<< orphan*/  umad_client ; 

__attribute__((used)) static void ib_umad_add_one(struct ib_device *device)
{
	struct ib_umad_device *umad_dev;
	int s, e, i;

	if (rdma_node_get_transport(device->node_type) != RDMA_TRANSPORT_IB)
		return;

	if (device->node_type == RDMA_NODE_IB_SWITCH)
		s = e = 0;
	else {
		s = 1;
		e = device->phys_port_cnt;
	}

	umad_dev = kzalloc(sizeof *umad_dev +
			   (e - s + 1) * sizeof (struct ib_umad_port),
			   GFP_KERNEL);
	if (!umad_dev)
		return;

	kref_init(&umad_dev->ref);

	umad_dev->start_port = s;
	umad_dev->end_port   = e;

	for (i = s; i <= e; ++i) {
		umad_dev->port[i - s].umad_dev = umad_dev;

		if (ib_umad_init_port(device, i, &umad_dev->port[i - s]))
			goto err;
	}

	ib_set_client_data(device, &umad_client, umad_dev);

	return;

err:
	while (--i >= s)
		ib_umad_kill_port(&umad_dev->port[i - s]);

	kref_put(&umad_dev->ref, ib_umad_release_dev);
}