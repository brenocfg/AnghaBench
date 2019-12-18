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
struct inet6_dev {int /*<<< orphan*/  mc_maxdelay; scalar_t__ mc_ifc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_ifc_start_timer (struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mld_send_cr (struct inet6_dev*) ; 

__attribute__((used)) static void mld_ifc_timer_expire(unsigned long data)
{
	struct inet6_dev *idev = (struct inet6_dev *)data;

	mld_send_cr(idev);
	if (idev->mc_ifc_count) {
		idev->mc_ifc_count--;
		if (idev->mc_ifc_count)
			mld_ifc_start_timer(idev, idev->mc_maxdelay);
	}
	__in6_dev_put(idev);
}