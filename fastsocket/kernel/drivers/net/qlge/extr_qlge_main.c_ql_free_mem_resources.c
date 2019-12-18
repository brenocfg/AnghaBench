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
struct ql_adapter {int tx_ring_count; int rx_ring_count; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_free_rx_resources (struct ql_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_free_shadow_space (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_free_tx_resources (struct ql_adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_free_mem_resources(struct ql_adapter *qdev)
{
	int i;

	for (i = 0; i < qdev->tx_ring_count; i++)
		ql_free_tx_resources(qdev, &qdev->tx_ring[i]);
	for (i = 0; i < qdev->rx_ring_count; i++)
		ql_free_rx_resources(qdev, &qdev->rx_ring[i]);
	ql_free_shadow_space(qdev);
}