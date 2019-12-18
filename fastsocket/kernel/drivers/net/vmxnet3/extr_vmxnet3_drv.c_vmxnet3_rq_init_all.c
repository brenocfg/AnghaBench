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
struct vmxnet3_adapter {int num_rx_queues; TYPE_1__* netdev; int /*<<< orphan*/ * rx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int vmxnet3_rq_init (int /*<<< orphan*/ *,struct vmxnet3_adapter*) ; 

__attribute__((used)) static int
vmxnet3_rq_init_all(struct vmxnet3_adapter *adapter)
{
	int i, err = 0;

	for (i = 0; i < adapter->num_rx_queues; i++) {
		err = vmxnet3_rq_init(&adapter->rx_queue[i], adapter);
		if (unlikely(err)) {
			dev_err(&adapter->netdev->dev, "%s: failed to "
				"initialize rx queue%i\n",
				adapter->netdev->name, i);
			break;
		}
	}
	return err;

}