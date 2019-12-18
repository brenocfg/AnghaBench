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
struct xt_tgchk_param {struct ipt_entry* entryinfo; struct ipt_reject_info* targinfo; } ;
struct ipt_reject_info {scalar_t__ with; } ;
struct TYPE_2__ {scalar_t__ proto; int invflags; } ;
struct ipt_entry {TYPE_1__ ip; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPT_ICMP_ECHOREPLY ; 
 scalar_t__ IPT_TCP_RESET ; 
 int XT_INV_PROTO ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static bool reject_tg_check(const struct xt_tgchk_param *par)
{
	const struct ipt_reject_info *rejinfo = par->targinfo;
	const struct ipt_entry *e = par->entryinfo;

	if (rejinfo->with == IPT_ICMP_ECHOREPLY) {
		printk("ipt_REJECT: ECHOREPLY no longer supported.\n");
		return false;
	} else if (rejinfo->with == IPT_TCP_RESET) {
		/* Must specify that it's a TCP packet */
		if (e->ip.proto != IPPROTO_TCP
		    || (e->ip.invflags & XT_INV_PROTO)) {
			printk("ipt_REJECT: TCP_RESET invalid for non-tcp\n");
			return false;
		}
	}
	return true;
}