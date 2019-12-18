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
struct ip_mc_list {int users; size_t sfmode; int* sfcount; int /*<<< orphan*/  multiaddr; struct ip_mc_list* next; scalar_t__ loaded; scalar_t__ gsquery; scalar_t__ reporter; int /*<<< orphan*/  unsolicit_count; int /*<<< orphan*/  timer; scalar_t__ tm_running; int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; scalar_t__ crcount; int /*<<< orphan*/ * tomb; int /*<<< orphan*/ * sources; struct in_device* interface; } ;
struct in_device {int /*<<< orphan*/  dead; int /*<<< orphan*/  mc_list_lock; int /*<<< orphan*/  mc_count; struct ip_mc_list* mc_list; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IGMP_Unsolicited_Report_Count ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  igmp_group_added (struct ip_mc_list*) ; 
 int /*<<< orphan*/  igmp_timer_expire ; 
 int /*<<< orphan*/  igmpv3_del_delrec (struct in_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_dev_hold (struct in_device*) ; 
 int /*<<< orphan*/  ip_mc_add_src (struct in_device*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_multicast_event (struct in_device*) ; 
 struct ip_mc_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ip_mc_inc_group(struct in_device *in_dev, __be32 addr)
{
	struct ip_mc_list *im;

	ASSERT_RTNL();

	for (im=in_dev->mc_list; im; im=im->next) {
		if (im->multiaddr == addr) {
			im->users++;
			ip_mc_add_src(in_dev, &addr, MCAST_EXCLUDE, 0, NULL, 0);
			goto out;
		}
	}

	im = kmalloc(sizeof(*im), GFP_KERNEL);
	if (!im)
		goto out;

	im->users = 1;
	im->interface = in_dev;
	in_dev_hold(in_dev);
	im->multiaddr = addr;
	/* initial mode is (EX, empty) */
	im->sfmode = MCAST_EXCLUDE;
	im->sfcount[MCAST_INCLUDE] = 0;
	im->sfcount[MCAST_EXCLUDE] = 1;
	im->sources = NULL;
	im->tomb = NULL;
	im->crcount = 0;
	atomic_set(&im->refcnt, 1);
	spin_lock_init(&im->lock);
#ifdef CONFIG_IP_MULTICAST
	im->tm_running = 0;
	setup_timer(&im->timer, &igmp_timer_expire, (unsigned long)im);
	im->unsolicit_count = IGMP_Unsolicited_Report_Count;
	im->reporter = 0;
	im->gsquery = 0;
#endif
	im->loaded = 0;
	write_lock_bh(&in_dev->mc_list_lock);
	im->next = in_dev->mc_list;
	in_dev->mc_list = im;
	in_dev->mc_count++;
	write_unlock_bh(&in_dev->mc_list_lock);
#ifdef CONFIG_IP_MULTICAST
	igmpv3_del_delrec(in_dev, im->multiaddr);
#endif
	igmp_group_added(im);
	if (!in_dev->dead)
		ip_rt_multicast_event(in_dev);
out:
	return;
}