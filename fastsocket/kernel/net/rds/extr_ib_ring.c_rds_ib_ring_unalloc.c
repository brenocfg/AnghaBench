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
typedef  int u32 ;
struct rds_ib_work_ring {int w_alloc_ptr; int w_nr; int /*<<< orphan*/  w_alloc_ctr; } ;

/* Variables and functions */

void rds_ib_ring_unalloc(struct rds_ib_work_ring *ring, u32 val)
{
	ring->w_alloc_ptr = (ring->w_alloc_ptr - val) % ring->w_nr;
	ring->w_alloc_ctr -= val;
}