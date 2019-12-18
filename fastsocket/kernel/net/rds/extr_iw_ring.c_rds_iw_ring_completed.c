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
typedef  unsigned long long u32 ;
struct rds_iw_work_ring {int /*<<< orphan*/  w_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdsdebug (char*,struct rds_iw_work_ring*,unsigned long long,unsigned long long,unsigned long long) ; 

u32 rds_iw_ring_completed(struct rds_iw_work_ring *ring, u32 wr_id, u32 oldest)
{
	u32 ret;

	if (oldest <= (unsigned long long)wr_id)
		ret = (unsigned long long)wr_id - oldest + 1;
	else
		ret = ring->w_nr - oldest + (unsigned long long)wr_id + 1;

	rdsdebug("ring %p ret %u wr_id %u oldest %u\n", ring, ret,
		 wr_id, oldest);
	return ret;
}