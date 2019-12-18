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
struct in_device {int /*<<< orphan*/  mc_tomb_lock; int /*<<< orphan*/  mc_list_lock; int /*<<< orphan*/  mr_qrv; int /*<<< orphan*/  mr_ifc_timer; scalar_t__ mc_count; scalar_t__ mr_ifc_count; int /*<<< orphan*/  mr_gq_timer; scalar_t__ mr_gq_running; int /*<<< orphan*/ * mc_tomb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  IGMP_Unsolicited_Report_Count ; 
 int /*<<< orphan*/  igmp_gq_timer_expire ; 
 int /*<<< orphan*/  igmp_ifc_timer_expire ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ip_mc_init_dev(struct in_device *in_dev)
{
	ASSERT_RTNL();

	in_dev->mc_tomb = NULL;
#ifdef CONFIG_IP_MULTICAST
	in_dev->mr_gq_running = 0;
	setup_timer(&in_dev->mr_gq_timer, igmp_gq_timer_expire,
			(unsigned long)in_dev);
	in_dev->mr_ifc_count = 0;
	in_dev->mc_count     = 0;
	setup_timer(&in_dev->mr_ifc_timer, igmp_ifc_timer_expire,
			(unsigned long)in_dev);
	in_dev->mr_qrv = IGMP_Unsolicited_Report_Count;
#endif

	rwlock_init(&in_dev->mc_list_lock);
	spin_lock_init(&in_dev->mc_tomb_lock);
}