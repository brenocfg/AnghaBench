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
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; int /*<<< orphan*/  mc_gq_timer; scalar_t__ mc_gq_running; int /*<<< orphan*/  mc_ifc_timer; scalar_t__ mc_ifc_count; } ;
struct ifmcaddr6 {struct ifmcaddr6* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __in6_dev_put (struct inet6_dev*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igmp6_group_dropped (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  mld_clear_delrec (struct inet6_dev*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

void ipv6_mc_down(struct inet6_dev *idev)
{
	struct ifmcaddr6 *i;

	/* Withdraw multicast list */

	read_lock_bh(&idev->lock);
	idev->mc_ifc_count = 0;
	if (del_timer(&idev->mc_ifc_timer))
		__in6_dev_put(idev);
	idev->mc_gq_running = 0;
	if (del_timer(&idev->mc_gq_timer))
		__in6_dev_put(idev);

	for (i = idev->mc_list; i; i=i->next)
		igmp6_group_dropped(i);
	read_unlock_bh(&idev->lock);

	mld_clear_delrec(idev);
}