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
struct TYPE_2__ {scalar_t__ toggle; } ;
struct ibmveth_adapter {TYPE_1__ rx_queue; } ;

/* Variables and functions */
 scalar_t__ ibmveth_rxq_toggle (struct ibmveth_adapter*) ; 

__attribute__((used)) static inline int ibmveth_rxq_pending_buffer(struct ibmveth_adapter *adapter)
{
	return ibmveth_rxq_toggle(adapter) == adapter->rx_queue.toggle;
}