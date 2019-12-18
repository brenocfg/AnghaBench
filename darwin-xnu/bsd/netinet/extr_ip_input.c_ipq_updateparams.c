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

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  frag_sched_timeout () ; 
 int ipq_limit ; 
 int /*<<< orphan*/  ipqlock ; 
 scalar_t__ maxnipq ; 

__attribute__((used)) static void
ipq_updateparams(void)
{
	LCK_MTX_ASSERT(&ipqlock, LCK_MTX_ASSERT_OWNED);
	/*
	 * -1 for unlimited allocation.
	 */
	if (maxnipq < 0)
		ipq_limit = 0;
	/*
	 * Positive number for specific bound.
	 */
	if (maxnipq > 0)
		ipq_limit = maxnipq;
	/*
	 * Zero specifies no further fragment queue allocation -- set the
	 * bound very low, but rely on implementation elsewhere to actually
	 * prevent allocation and reclaim current queues.
	 */
	if (maxnipq == 0)
		ipq_limit = 1;
	/*
	 * Arm the purge timer if not already and if there's work to do
	 */
	frag_sched_timeout();
}