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
typedef  int /*<<< orphan*/  u32 ;
struct rds_iw_work_ring {int /*<<< orphan*/  w_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rds_iw_ring_used (struct rds_iw_work_ring*) ; 

void rds_iw_ring_resize(struct rds_iw_work_ring *ring, u32 nr)
{
	/* We only ever get called from the connection setup code,
	 * prior to creating the QP. */
	BUG_ON(__rds_iw_ring_used(ring));
	ring->w_nr = nr;
}