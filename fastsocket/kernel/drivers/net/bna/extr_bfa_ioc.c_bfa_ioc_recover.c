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
struct bfa_ioc {int /*<<< orphan*/  hb_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOC_E_HBFAIL ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_stats (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_stats_hb_count (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_hbfails ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static void
bfa_ioc_recover(struct bfa_ioc *ioc)
{
	pr_crit("Heart Beat of IOC has failed\n");
	bfa_ioc_stats(ioc, ioc_hbfails);
	bfa_ioc_stats_hb_count(ioc, ioc->hb_count);
	bfa_fsm_send_event(ioc, IOC_E_HBFAIL);
}