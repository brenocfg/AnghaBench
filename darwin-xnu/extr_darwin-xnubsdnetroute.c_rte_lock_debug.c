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
typedef  size_t uint32_t ;
struct rtentry_dbg {int /*<<< orphan*/ * rtd_lock; int /*<<< orphan*/  rtd_lock_cnt; } ;
struct rtentry {int dummy; } ;

/* Variables and functions */
 size_t CTRACE_HIST_SIZE ; 
 int RTD_TRACE ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 size_t atomic_add_32_ov (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ctrace_record (int /*<<< orphan*/ *) ; 
 int rte_debug ; 

__attribute__((used)) static inline void
rte_lock_debug(struct rtentry_dbg *rte)
{
	uint32_t idx;

	RT_LOCK_ASSERT_HELD((struct rtentry *)rte);
	idx = atomic_add_32_ov(&rte->rtd_lock_cnt, 1) % CTRACE_HIST_SIZE;
	if (rte_debug & RTD_TRACE)
		ctrace_record(&rte->rtd_lock[idx]);
}