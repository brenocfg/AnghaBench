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
struct rx_ring {scalar_t__ type; } ;
struct ql_adapter {int rx_ring_count; struct rx_ring* rx_ring; } ;

/* Variables and functions */
 scalar_t__ TX_Q ; 
 int /*<<< orphan*/  ql_update_buffer_queues (struct ql_adapter*,struct rx_ring*) ; 

__attribute__((used)) static void ql_alloc_rx_buffers(struct ql_adapter *qdev)
{
	struct rx_ring *rx_ring;
	int i;

	for (i = 0; i < qdev->rx_ring_count; i++) {
		rx_ring = &qdev->rx_ring[i];
		if (rx_ring->type != TX_Q)
			ql_update_buffer_queues(qdev, rx_ring);
	}
}