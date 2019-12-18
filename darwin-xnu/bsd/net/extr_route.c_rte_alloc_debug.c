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
struct rtentry_dbg {int /*<<< orphan*/  rtd_inuse; int /*<<< orphan*/  rtd_alloc; } ;
struct rtentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTD_INUSE ; 
 int RTD_TRACE ; 
 int /*<<< orphan*/  bzero (struct rtentry_dbg*,int) ; 
 int /*<<< orphan*/  ctrace_record (int /*<<< orphan*/ *) ; 
 int rte_debug ; 
 int /*<<< orphan*/  rte_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct rtentry *
rte_alloc_debug(void)
{
	struct rtentry_dbg *rte;

	rte = ((struct rtentry_dbg *)zalloc(rte_zone));
	if (rte != NULL) {
		bzero(rte, sizeof (*rte));
		if (rte_debug & RTD_TRACE)
			ctrace_record(&rte->rtd_alloc);
		rte->rtd_inuse = RTD_INUSE;
	}
	return ((struct rtentry *)rte);
}