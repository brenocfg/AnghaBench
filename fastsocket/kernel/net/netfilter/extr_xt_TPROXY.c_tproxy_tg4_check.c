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
struct xt_tgchk_param {struct ipt_ip* entryinfo; } ;
struct ipt_ip {scalar_t__ proto; int invflags; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int IPT_INV_PROTO ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static bool tproxy_tg4_check(const struct xt_tgchk_param *par)
{
	const struct ipt_ip *i = par->entryinfo;

	if ((i->proto == IPPROTO_TCP || i->proto == IPPROTO_UDP)
	    && !(i->invflags & IPT_INV_PROTO))
		return true;

	pr_info("xt_TPROXY: Can be used only in combination with "
		"either -p tcp or -p udp\n");
	return false;
}