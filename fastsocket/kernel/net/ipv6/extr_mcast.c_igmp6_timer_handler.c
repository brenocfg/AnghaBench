#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifmcaddr6 {int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_flags; TYPE_1__* idev; int /*<<< orphan*/  mca_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_MGM_REPORT ; 
 int /*<<< orphan*/  MAF_LAST_REPORTER ; 
 int /*<<< orphan*/  MAF_TIMER_RUNNING ; 
 scalar_t__ MLD_V1_SEEN (TYPE_1__*) ; 
 int /*<<< orphan*/  igmp6_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ma_put (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_send_report (TYPE_1__*,struct ifmcaddr6*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igmp6_timer_handler(unsigned long data)
{
	struct ifmcaddr6 *ma = (struct ifmcaddr6 *) data;

	if (MLD_V1_SEEN(ma->idev))
		igmp6_send(&ma->mca_addr, ma->idev->dev, ICMPV6_MGM_REPORT);
	else
		mld_send_report(ma->idev, ma);

	spin_lock(&ma->mca_lock);
	ma->mca_flags |=  MAF_LAST_REPORTER;
	ma->mca_flags &= ~MAF_TIMER_RUNNING;
	spin_unlock(&ma->mca_lock);
	ma_put(ma);
}