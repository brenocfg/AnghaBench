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
struct xt_target_param {scalar_t__ targinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  printk (char*,char const*) ; 

__attribute__((used)) static unsigned int
arpt_error(struct sk_buff *skb, const struct xt_target_param *par)
{
	if (net_ratelimit())
		printk("arp_tables: error: '%s'\n",
		       (const char *)par->targinfo);

	return NF_DROP;
}