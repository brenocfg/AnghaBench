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
typedef  scalar_t__ u32 ;
struct rds_iw_work_ring {scalar_t__ w_alloc_ctr; scalar_t__ w_nr; int /*<<< orphan*/  w_free_ctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 __rds_iw_ring_used(struct rds_iw_work_ring *ring)
{
	u32 diff;

	/* This assumes that atomic_t has at least as many bits as u32 */
	diff = ring->w_alloc_ctr - (u32) atomic_read(&ring->w_free_ctr);
	BUG_ON(diff > ring->w_nr);

	return diff;
}