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
struct rds_iw_work_ring {int w_free_ptr; int w_nr; int /*<<< orphan*/  w_free_ctr; } ;

/* Variables and functions */
 scalar_t__ __rds_iw_ring_empty (struct rds_iw_work_ring*) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_iw_ring_empty_wait ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void rds_iw_ring_free(struct rds_iw_work_ring *ring, u32 val)
{
	ring->w_free_ptr = (ring->w_free_ptr + val) % ring->w_nr;
	atomic_add(val, &ring->w_free_ctr);

	if (__rds_iw_ring_empty(ring) &&
	    waitqueue_active(&rds_iw_ring_empty_wait))
		wake_up(&rds_iw_ring_empty_wait);
}