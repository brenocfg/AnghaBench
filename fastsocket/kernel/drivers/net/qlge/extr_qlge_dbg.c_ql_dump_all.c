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
struct wqicb {int dummy; } ;
struct ql_adapter {int tx_ring_count; int rx_ring_count; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * tx_ring; } ;
struct cqicb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DUMP_CQICB (struct cqicb*) ; 
 int /*<<< orphan*/  QL_DUMP_QDEV (struct ql_adapter*) ; 
 int /*<<< orphan*/  QL_DUMP_REGS (struct ql_adapter*) ; 
 int /*<<< orphan*/  QL_DUMP_RX_RING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QL_DUMP_TX_RING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QL_DUMP_WQICB (struct wqicb*) ; 

void ql_dump_all(struct ql_adapter *qdev)
{
	int i;

	QL_DUMP_REGS(qdev);
	QL_DUMP_QDEV(qdev);
	for (i = 0; i < qdev->tx_ring_count; i++) {
		QL_DUMP_TX_RING(&qdev->tx_ring[i]);
		QL_DUMP_WQICB((struct wqicb *)&qdev->tx_ring[i]);
	}
	for (i = 0; i < qdev->rx_ring_count; i++) {
		QL_DUMP_RX_RING(&qdev->rx_ring[i]);
		QL_DUMP_CQICB((struct cqicb *)&qdev->rx_ring[i]);
	}
}