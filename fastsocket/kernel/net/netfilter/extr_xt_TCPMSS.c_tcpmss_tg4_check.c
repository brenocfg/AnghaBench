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
struct xt_tgchk_param {int hook_mask; struct ipt_entry* entryinfo; struct xt_tcpmss_info* targinfo; } ;
struct xt_tcpmss_info {scalar_t__ mss; } ;
struct ipt_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPT_MATCH_ITERATE (struct ipt_entry const*,int /*<<< orphan*/ ) ; 
 int NF_INET_FORWARD ; 
 int NF_INET_LOCAL_OUT ; 
 int NF_INET_POST_ROUTING ; 
 scalar_t__ XT_TCPMSS_CLAMP_PMTU ; 
 int /*<<< orphan*/  find_syn_match ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static bool tcpmss_tg4_check(const struct xt_tgchk_param *par)
{
	const struct xt_tcpmss_info *info = par->targinfo;
	const struct ipt_entry *e = par->entryinfo;

	if (info->mss == XT_TCPMSS_CLAMP_PMTU &&
	    (par->hook_mask & ~((1 << NF_INET_FORWARD) |
			   (1 << NF_INET_LOCAL_OUT) |
			   (1 << NF_INET_POST_ROUTING))) != 0) {
		printk("xt_TCPMSS: path-MTU clamping only supported in "
		       "FORWARD, OUTPUT and POSTROUTING hooks\n");
		return false;
	}
	if (IPT_MATCH_ITERATE(e, find_syn_match))
		return true;
	printk("xt_TCPMSS: Only works on TCP SYN packets\n");
	return false;
}