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
 int /*<<< orphan*/  memset (struct rds_iw_work_ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_iw_work_ring*,int /*<<< orphan*/ ) ; 

void rds_iw_ring_init(struct rds_iw_work_ring *ring, u32 nr)
{
	memset(ring, 0, sizeof(*ring));
	ring->w_nr = nr;
	rdsdebug("ring %p nr %u\n", ring, ring->w_nr);
}