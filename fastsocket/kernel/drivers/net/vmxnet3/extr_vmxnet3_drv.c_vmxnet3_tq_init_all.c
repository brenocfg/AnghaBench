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
struct vmxnet3_adapter {int num_tx_queues; int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmxnet3_tq_init (int /*<<< orphan*/ *,struct vmxnet3_adapter*) ; 

__attribute__((used)) static void
vmxnet3_tq_init_all(struct vmxnet3_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_tx_queues; i++)
		vmxnet3_tq_init(&adapter->tx_queue[i], adapter);
}