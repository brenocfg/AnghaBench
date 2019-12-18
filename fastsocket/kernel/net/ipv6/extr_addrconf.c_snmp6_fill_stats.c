#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ icmpv6; scalar_t__ ipv6; } ;
struct inet6_dev {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6_MIB_MAX ; 
#define  IFLA_INET6_ICMP6STATS 129 
#define  IFLA_INET6_STATS 128 
 int /*<<< orphan*/  IPSTATS_MIB_MAX ; 
 int /*<<< orphan*/  __snmp6_fill_stats (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snmp6_fill_stats(u64 *stats, struct inet6_dev *idev, int attrtype,
			     int bytes)
{
	switch(attrtype) {
	case IFLA_INET6_STATS:
		__snmp6_fill_stats(stats, (void **)idev->stats.ipv6, IPSTATS_MIB_MAX, bytes);
		break;
	case IFLA_INET6_ICMP6STATS:
		__snmp6_fill_stats(stats, (void **)idev->stats.icmpv6, ICMP6_MIB_MAX, bytes);
		break;
	}
}