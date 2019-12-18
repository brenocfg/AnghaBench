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
struct rx_ring {int dummy; } ;
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_update_lbq (struct ql_adapter*,struct rx_ring*) ; 
 int /*<<< orphan*/  ql_update_sbq (struct ql_adapter*,struct rx_ring*) ; 

__attribute__((used)) static void ql_update_buffer_queues(struct ql_adapter *qdev,
				    struct rx_ring *rx_ring)
{
	ql_update_sbq(qdev, rx_ring);
	ql_update_lbq(qdev, rx_ring);
}