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
struct bnx2x {int /*<<< orphan*/  stats_sema; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int HZ ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int /*<<< orphan*/  __bnx2x_stats_start (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_comp (struct bnx2x*) ; 
 scalar_t__ down_timeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_stats_restart(struct bnx2x *bp)
{
	/* vfs travel through here as part of the statistics FSM, but no action
	 * is required
	 */
	if (IS_VF(bp))
		return;
	if (down_timeout(&bp->stats_sema, HZ/10))
		BNX2X_ERR("Unable to acquire stats lock\n");
	bnx2x_stats_comp(bp);
	__bnx2x_stats_start(bp);
	up(&bp->stats_sema);
}