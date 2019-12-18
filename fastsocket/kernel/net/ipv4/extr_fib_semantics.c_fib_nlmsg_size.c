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
struct rtnexthop {int dummy; } ;
struct rtmsg {int dummy; } ;
struct fib_info {int fib_nhs; } ;

/* Variables and functions */
 int NLMSG_ALIGN (int) ; 
 size_t RTAX_MAX ; 
 int nla_total_size (size_t) ; 

__attribute__((used)) static inline size_t fib_nlmsg_size(struct fib_info *fi)
{
	size_t payload = NLMSG_ALIGN(sizeof(struct rtmsg))
			 + nla_total_size(4) /* RTA_TABLE */
			 + nla_total_size(4) /* RTA_DST */
			 + nla_total_size(4) /* RTA_PRIORITY */
			 + nla_total_size(4); /* RTA_PREFSRC */

	/* space for nested metrics */
	payload += nla_total_size((RTAX_MAX * nla_total_size(4)));

	if (fi->fib_nhs) {
		/* Also handles the special case fib_nhs == 1 */

		/* each nexthop is packed in an attribute */
		size_t nhsize = nla_total_size(sizeof(struct rtnexthop));

		/* may contain flow and gateway attribute */
		nhsize += 2 * nla_total_size(4);

		/* all nexthops are packed in a nested attribute */
		payload += nla_total_size(fi->fib_nhs * nhsize);
	}

	return payload;
}