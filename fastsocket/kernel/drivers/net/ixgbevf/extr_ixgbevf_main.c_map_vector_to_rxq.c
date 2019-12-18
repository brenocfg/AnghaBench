#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  count; TYPE_2__* ring; } ;
struct ixgbevf_q_vector {TYPE_1__ rx; } ;
struct ixgbevf_adapter {TYPE_2__* rx_ring; struct ixgbevf_q_vector** q_vector; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void map_vector_to_rxq(struct ixgbevf_adapter *a, int v_idx,
				     int r_idx)
{
	struct ixgbevf_q_vector *q_vector = a->q_vector[v_idx];

	a->rx_ring[r_idx].next = q_vector->rx.ring;
	q_vector->rx.ring = &a->rx_ring[r_idx];
	q_vector->rx.count++;
}