#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ifmcaddr6 {int mca_flags; TYPE_1__* idev; int /*<<< orphan*/  mca_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_MGM_REDUCTION ; 
 int MAF_LAST_REPORTER ; 
 scalar_t__ MLD_V1_SEEN (TYPE_1__*) ; 
 int /*<<< orphan*/  igmp6_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mld_add_delrec (TYPE_1__*,struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_ifc_event (TYPE_1__*) ; 

__attribute__((used)) static void igmp6_leave_group(struct ifmcaddr6 *ma)
{
	if (MLD_V1_SEEN(ma->idev)) {
		if (ma->mca_flags & MAF_LAST_REPORTER)
			igmp6_send(&ma->mca_addr, ma->idev->dev,
				ICMPV6_MGM_REDUCTION);
	} else {
		mld_add_delrec(ma->idev, ma);
		mld_ifc_event(ma->idev);
	}
}