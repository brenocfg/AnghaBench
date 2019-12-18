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
struct ip_mc_list {int loaded; scalar_t__ crcount; int /*<<< orphan*/  lock; int /*<<< orphan*/  multiaddr; struct in_device* interface; } ;
struct in_device {scalar_t__ mr_qrv; scalar_t__ dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGMP_ALL_HOSTS ; 
 int /*<<< orphan*/  IGMP_Initial_Report_Delay ; 
 scalar_t__ IGMP_Unsolicited_Report_Count ; 
 scalar_t__ IGMP_V1_SEEN (struct in_device*) ; 
 scalar_t__ IGMP_V2_SEEN (struct in_device*) ; 
 int /*<<< orphan*/  igmp_ifc_event (struct in_device*) ; 
 int /*<<< orphan*/  igmp_start_timer (struct ip_mc_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_mc_filter_add (struct in_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igmp_group_added(struct ip_mc_list *im)
{
	struct in_device *in_dev = im->interface;

	if (im->loaded == 0) {
		im->loaded = 1;
		ip_mc_filter_add(in_dev, im->multiaddr);
	}

#ifdef CONFIG_IP_MULTICAST
	if (im->multiaddr == IGMP_ALL_HOSTS)
		return;

	if (in_dev->dead)
		return;
	if (IGMP_V1_SEEN(in_dev) || IGMP_V2_SEEN(in_dev)) {
		spin_lock_bh(&im->lock);
		igmp_start_timer(im, IGMP_Initial_Report_Delay);
		spin_unlock_bh(&im->lock);
		return;
	}
	/* else, v3 */

	im->crcount = in_dev->mr_qrv ? in_dev->mr_qrv :
		IGMP_Unsolicited_Report_Count;
	igmp_ifc_event(in_dev);
#endif
}