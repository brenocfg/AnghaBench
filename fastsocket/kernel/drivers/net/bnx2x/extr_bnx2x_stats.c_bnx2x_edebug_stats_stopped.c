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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ EDEBUG_DRIVER_IF_OP_CODE_DISABLE_STAT ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * edebug_driver_if ; 

__attribute__((used)) static bool bnx2x_edebug_stats_stopped(struct bnx2x *bp)
{
	u32 val;

	if (SHMEM2_HAS(bp, edebug_driver_if[1])) {
		val = SHMEM2_RD(bp, edebug_driver_if[1]);

		if (val == EDEBUG_DRIVER_IF_OP_CODE_DISABLE_STAT)
			return true;
	}

	return false;
}