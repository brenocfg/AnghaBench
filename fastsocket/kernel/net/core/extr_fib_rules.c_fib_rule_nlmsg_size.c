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
struct fib_rules_ops {scalar_t__ (* nlmsg_payload ) (struct fib_rule*) ;} ;
struct fib_rule_hdr {int dummy; } ;
struct fib_rule {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 
 scalar_t__ stub1 (struct fib_rule*) ; 

__attribute__((used)) static inline size_t fib_rule_nlmsg_size(struct fib_rules_ops *ops,
					 struct fib_rule *rule)
{
	size_t payload = NLMSG_ALIGN(sizeof(struct fib_rule_hdr))
			 + nla_total_size(IFNAMSIZ) /* FRA_IFNAME */
			 + nla_total_size(4) /* FRA_PRIORITY */
			 + nla_total_size(4) /* FRA_TABLE */
			 + nla_total_size(4) /* FRA_FWMARK */
			 + nla_total_size(4); /* FRA_FWMASK */

	if (ops->nlmsg_payload)
		payload += ops->nlmsg_payload(rule);

	return payload;
}