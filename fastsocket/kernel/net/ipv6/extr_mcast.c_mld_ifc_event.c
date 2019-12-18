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
struct inet6_dev {int /*<<< orphan*/  mc_qrv; int /*<<< orphan*/  mc_ifc_count; } ;

/* Variables and functions */
 scalar_t__ MLD_V1_SEEN (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_ifc_start_timer (struct inet6_dev*,int) ; 

__attribute__((used)) static void mld_ifc_event(struct inet6_dev *idev)
{
	if (MLD_V1_SEEN(idev))
		return;
	idev->mc_ifc_count = idev->mc_qrv;
	mld_ifc_start_timer(idev, 1);
}