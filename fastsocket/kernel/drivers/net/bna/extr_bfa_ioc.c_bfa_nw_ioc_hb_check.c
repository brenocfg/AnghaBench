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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  heartbeat; } ;
struct bfa_ioc {scalar_t__ hb_count; int /*<<< orphan*/  hb_timer; TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_HB_TOV ; 
 int /*<<< orphan*/  bfa_ioc_mbox_poll (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_recover (struct bfa_ioc*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

void
bfa_nw_ioc_hb_check(void *cbarg)
{
	struct bfa_ioc *ioc = cbarg;
	u32	hb_count;

	hb_count = readl(ioc->ioc_regs.heartbeat);
	if (ioc->hb_count == hb_count) {
		bfa_ioc_recover(ioc);
		return;
	} else {
		ioc->hb_count = hb_count;
	}

	bfa_ioc_mbox_poll(ioc);
	mod_timer(&ioc->hb_timer, jiffies +
		msecs_to_jiffies(BFA_IOC_HB_TOV));
}