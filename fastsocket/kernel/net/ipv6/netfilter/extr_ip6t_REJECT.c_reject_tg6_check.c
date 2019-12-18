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
struct xt_tgchk_param {struct ip6t_entry* entryinfo; struct ip6t_reject_info* targinfo; } ;
struct ip6t_reject_info {scalar_t__ with; } ;
struct TYPE_2__ {scalar_t__ proto; int invflags; } ;
struct ip6t_entry {TYPE_1__ ipv6; } ;

/* Variables and functions */
 scalar_t__ IP6T_ICMP6_ECHOREPLY ; 
 scalar_t__ IP6T_TCP_RESET ; 
 scalar_t__ IPPROTO_TCP ; 
 int XT_INV_PROTO ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static bool reject_tg6_check(const struct xt_tgchk_param *par)
{
	const struct ip6t_reject_info *rejinfo = par->targinfo;
	const struct ip6t_entry *e = par->entryinfo;

	if (rejinfo->with == IP6T_ICMP6_ECHOREPLY) {
		printk("ip6t_REJECT: ECHOREPLY is not supported.\n");
		return false;
	} else if (rejinfo->with == IP6T_TCP_RESET) {
		/* Must specify that it's a TCP packet */
		if (e->ipv6.proto != IPPROTO_TCP
		    || (e->ipv6.invflags & XT_INV_PROTO)) {
			printk("ip6t_REJECT: TCP_RESET illegal for non-tcp\n");
			return false;
		}
	}
	return true;
}