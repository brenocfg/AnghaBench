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
struct ip_mc_list {scalar_t__ multiaddr; scalar_t__ users; struct ip_mc_list* next; } ;
struct in_device {int /*<<< orphan*/  dead; int /*<<< orphan*/  mc_list_lock; int /*<<< orphan*/  mc_count; struct ip_mc_list* mc_list; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  igmp_group_dropped (struct ip_mc_list*) ; 
 int /*<<< orphan*/  ip_ma_put (struct ip_mc_list*) ; 
 int /*<<< orphan*/  ip_mc_clear_src (struct ip_mc_list*) ; 
 int /*<<< orphan*/  ip_rt_multicast_event (struct in_device*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ip_mc_dec_group(struct in_device *in_dev, __be32 addr)
{
	struct ip_mc_list *i, **ip;

	ASSERT_RTNL();

	for (ip=&in_dev->mc_list; (i=*ip)!=NULL; ip=&i->next) {
		if (i->multiaddr == addr) {
			if (--i->users == 0) {
				write_lock_bh(&in_dev->mc_list_lock);
				*ip = i->next;
				in_dev->mc_count--;
				write_unlock_bh(&in_dev->mc_list_lock);
				igmp_group_dropped(i);
				ip_mc_clear_src(i);

				if (!in_dev->dead)
					ip_rt_multicast_event(in_dev);

				ip_ma_put(i);
				return;
			}
			break;
		}
	}
}