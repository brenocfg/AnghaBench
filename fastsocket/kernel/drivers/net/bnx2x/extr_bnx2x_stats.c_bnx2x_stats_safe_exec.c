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
 int /*<<< orphan*/  __bnx2x_stats_start (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_comp (struct bnx2x*) ; 
 scalar_t__ down_timeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void bnx2x_stats_safe_exec(struct bnx2x *bp,
			   void (func_to_exec)(void *cookie),
			   void *cookie){
	if (down_timeout(&bp->stats_sema, HZ/10))
		BNX2X_ERR("Unable to acquire stats lock\n");
	bnx2x_stats_comp(bp);
	func_to_exec(cookie);
	__bnx2x_stats_start(bp);
	up(&bp->stats_sema);
}