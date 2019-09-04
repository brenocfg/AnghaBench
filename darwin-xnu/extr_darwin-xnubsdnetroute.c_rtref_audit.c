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
typedef  size_t uint16_t ;
struct rtentry_dbg {scalar_t__ rtd_inuse; int /*<<< orphan*/ * rtd_refhold; int /*<<< orphan*/  rtd_refhold_cnt; } ;

/* Variables and functions */
 size_t CTRACE_HIST_SIZE ; 
 scalar_t__ RTD_INUSE ; 
 int RTD_TRACE ; 
 size_t atomic_add_16_ov (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ctrace_record (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,struct rtentry_dbg*) ; 
 int rte_debug ; 

__attribute__((used)) static inline void
rtref_audit(struct rtentry_dbg *rte)
{
	uint16_t idx;

	if (rte->rtd_inuse != RTD_INUSE) {
		panic("rtref_audit: on freed rte=%p\n", rte);
		/* NOTREACHED */
	}
	idx = atomic_add_16_ov(&rte->rtd_refhold_cnt, 1) % CTRACE_HIST_SIZE;
	if (rte_debug & RTD_TRACE)
		ctrace_record(&rte->rtd_refhold[idx]);
}