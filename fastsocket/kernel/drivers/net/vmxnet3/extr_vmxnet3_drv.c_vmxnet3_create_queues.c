#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_9__ {void* size; } ;
struct TYPE_8__ {void* size; } ;
struct TYPE_7__ {void* size; } ;
struct vmxnet3_tx_queue {int stopped; int qid; struct vmxnet3_adapter* adapter; int /*<<< orphan*/ * shared; TYPE_3__ comp_ring; TYPE_2__ data_ring; TYPE_1__ tx_ring; } ;
struct vmxnet3_rx_queue {struct vmxnet3_adapter* adapter; int /*<<< orphan*/ * shared; TYPE_5__* rx_ring; } ;
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; int /*<<< orphan*/  netdev; TYPE_6__* rqd_start; struct vmxnet3_rx_queue* rx_queue; TYPE_4__* tqd_start; struct vmxnet3_tx_queue* tx_queue; } ;
struct TYPE_12__ {int /*<<< orphan*/  ctrl; } ;
struct TYPE_11__ {void* size; } ;
struct TYPE_10__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vmxnet3_adjust_rx_ring_size (struct vmxnet3_adapter*) ; 
 int vmxnet3_rq_create (struct vmxnet3_rx_queue*,struct vmxnet3_adapter*) ; 
 int vmxnet3_tq_create (struct vmxnet3_tx_queue*,struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  vmxnet3_tq_destroy_all (struct vmxnet3_adapter*) ; 

int
vmxnet3_create_queues(struct vmxnet3_adapter *adapter, u32 tx_ring_size,
		      u32 rx_ring_size, u32 rx_ring2_size)
{
	int err = 0, i;

	for (i = 0; i < adapter->num_tx_queues; i++) {
		struct vmxnet3_tx_queue	*tq = &adapter->tx_queue[i];
		tq->tx_ring.size   = tx_ring_size;
		tq->data_ring.size = tx_ring_size;
		tq->comp_ring.size = tx_ring_size;
		tq->shared = &adapter->tqd_start[i].ctrl;
		tq->stopped = true;
		tq->adapter = adapter;
		tq->qid = i;
		err = vmxnet3_tq_create(tq, adapter);
		/*
		 * Too late to change num_tx_queues. We cannot do away with
		 * lesser number of queues than what we asked for
		 */
		if (err)
			goto queue_err;
	}

	adapter->rx_queue[0].rx_ring[0].size = rx_ring_size;
	adapter->rx_queue[0].rx_ring[1].size = rx_ring2_size;
	vmxnet3_adjust_rx_ring_size(adapter);
	for (i = 0; i < adapter->num_rx_queues; i++) {
		struct vmxnet3_rx_queue *rq = &adapter->rx_queue[i];
		/* qid and qid2 for rx queues will be assigned later when num
		 * of rx queues is finalized after allocating intrs */
		rq->shared = &adapter->rqd_start[i].ctrl;
		rq->adapter = adapter;
		err = vmxnet3_rq_create(rq, adapter);
		if (err) {
			if (i == 0) {
				netdev_err(adapter->netdev,
					   "Could not allocate any rx queues. "
					   "Aborting.\n");
				goto queue_err;
			} else {
				netdev_info(adapter->netdev,
					    "Number of rx queues changed "
					    "to : %d.\n", i);
				adapter->num_rx_queues = i;
				err = 0;
				break;
			}
		}
	}
	return err;
queue_err:
	vmxnet3_tq_destroy_all(adapter);
	return err;
}