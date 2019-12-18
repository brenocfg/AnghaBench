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
struct ip_mc_list {scalar_t__ multiaddr; struct in_device* interface; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGMPV2_HOST_MEMBERSHIP_REPORT ; 
 int /*<<< orphan*/  IGMPV3_HOST_MEMBERSHIP_REPORT ; 
 scalar_t__ IGMP_ALL_HOSTS ; 
 int /*<<< orphan*/  IGMP_HOST_MEMBERSHIP_REPORT ; 
 scalar_t__ IGMP_V1_SEEN (struct in_device*) ; 
 scalar_t__ IGMP_V2_SEEN (struct in_device*) ; 
 int /*<<< orphan*/  igmp_send_report (struct in_device*,struct ip_mc_list*,int /*<<< orphan*/ ) ; 

void ip_mc_rejoin_group(struct ip_mc_list *im)
{
#ifdef CONFIG_IP_MULTICAST
	struct in_device *in_dev = im->interface;

	if (im->multiaddr == IGMP_ALL_HOSTS)
		return;

	/* a failover is happening and switches
	 * must be notified immediately */
	if (IGMP_V1_SEEN(in_dev))
		igmp_send_report(in_dev, im, IGMP_HOST_MEMBERSHIP_REPORT);
	else if (IGMP_V2_SEEN(in_dev))
		igmp_send_report(in_dev, im, IGMPV2_HOST_MEMBERSHIP_REPORT);
	else
		igmp_send_report(in_dev, im, IGMPV3_HOST_MEMBERSHIP_REPORT);
#endif
}