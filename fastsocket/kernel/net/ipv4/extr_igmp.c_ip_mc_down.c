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
struct ip_mc_list {struct ip_mc_list* next; } ;
struct in_device {int /*<<< orphan*/  mr_gq_timer; scalar_t__ mr_gq_running; int /*<<< orphan*/  mr_ifc_timer; scalar_t__ mr_ifc_count; struct ip_mc_list* mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  IGMP_ALL_HOSTS ; 
 int /*<<< orphan*/  __in_dev_put (struct in_device*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igmp_group_dropped (struct ip_mc_list*) ; 
 int /*<<< orphan*/  igmpv3_clear_delrec (struct in_device*) ; 
 int /*<<< orphan*/  ip_mc_dec_group (struct in_device*,int /*<<< orphan*/ ) ; 

void ip_mc_down(struct in_device *in_dev)
{
	struct ip_mc_list *i;

	ASSERT_RTNL();

	for (i=in_dev->mc_list; i; i=i->next)
		igmp_group_dropped(i);

#ifdef CONFIG_IP_MULTICAST
	in_dev->mr_ifc_count = 0;
	if (del_timer(&in_dev->mr_ifc_timer))
		__in_dev_put(in_dev);
	in_dev->mr_gq_running = 0;
	if (del_timer(&in_dev->mr_gq_timer))
		__in_dev_put(in_dev);
	igmpv3_clear_delrec(in_dev);
#endif

	ip_mc_dec_group(in_dev, IGMP_ALL_HOSTS);
}