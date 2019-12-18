#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; int /*<<< orphan*/ * base; int /*<<< orphan*/  basePA; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * base; int /*<<< orphan*/  basePA; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/ * base; int /*<<< orphan*/  basePA; } ;
struct vmxnet3_tx_queue {int /*<<< orphan*/ * buf_info; TYPE_3__ comp_ring; TYPE_2__ data_ring; TYPE_1__ tx_ring; } ;
struct vmxnet3_adapter {int /*<<< orphan*/  pdev; } ;
struct Vmxnet3_TxDesc {int dummy; } ;
struct Vmxnet3_TxDataDesc {int dummy; } ;
struct Vmxnet3_TxCompDesc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_tq_destroy(struct vmxnet3_tx_queue *tq,
		   struct vmxnet3_adapter *adapter)
{
	if (tq->tx_ring.base) {
		pci_free_consistent(adapter->pdev, tq->tx_ring.size *
				    sizeof(struct Vmxnet3_TxDesc),
				    tq->tx_ring.base, tq->tx_ring.basePA);
		tq->tx_ring.base = NULL;
	}
	if (tq->data_ring.base) {
		pci_free_consistent(adapter->pdev, tq->data_ring.size *
				    sizeof(struct Vmxnet3_TxDataDesc),
				    tq->data_ring.base, tq->data_ring.basePA);
		tq->data_ring.base = NULL;
	}
	if (tq->comp_ring.base) {
		pci_free_consistent(adapter->pdev, tq->comp_ring.size *
				    sizeof(struct Vmxnet3_TxCompDesc),
				    tq->comp_ring.base, tq->comp_ring.basePA);
		tq->comp_ring.base = NULL;
	}
	kfree(tq->buf_info);
	tq->buf_info = NULL;
}