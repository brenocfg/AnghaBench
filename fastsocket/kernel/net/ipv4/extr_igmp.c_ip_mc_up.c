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
struct in_device {struct ip_mc_list* mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  IGMP_ALL_HOSTS ; 
 int /*<<< orphan*/  igmp_group_added (struct ip_mc_list*) ; 
 int /*<<< orphan*/  ip_mc_inc_group (struct in_device*,int /*<<< orphan*/ ) ; 

void ip_mc_up(struct in_device *in_dev)
{
	struct ip_mc_list *i;

	ASSERT_RTNL();

	ip_mc_inc_group(in_dev, IGMP_ALL_HOSTS);

	for (i=in_dev->mc_list; i; i=i->next)
		igmp_group_added(i);
}