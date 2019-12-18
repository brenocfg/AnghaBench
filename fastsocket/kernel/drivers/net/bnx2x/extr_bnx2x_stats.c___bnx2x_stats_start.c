#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bnx2x {int stats_started; scalar_t__ func_stx; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_func_stats_init (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_hw_stats_post (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_port_stats_init (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_storm_stats_post (struct bnx2x*) ; 

__attribute__((used)) static void __bnx2x_stats_start(struct bnx2x *bp)
{
	if (IS_PF(bp)) {
		if (bp->port.pmf)
			bnx2x_port_stats_init(bp);

		else if (bp->func_stx)
			bnx2x_func_stats_init(bp);

		bnx2x_hw_stats_post(bp);
		bnx2x_storm_stats_post(bp);
	}

	bp->stats_started = true;
}