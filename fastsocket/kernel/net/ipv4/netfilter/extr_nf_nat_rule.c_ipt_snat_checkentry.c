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
struct xt_tgchk_param {struct nf_nat_multi_range_compat* targinfo; } ;
struct nf_nat_multi_range_compat {int rangesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static bool ipt_snat_checkentry(const struct xt_tgchk_param *par)
{
	const struct nf_nat_multi_range_compat *mr = par->targinfo;

	/* Must be a valid range */
	if (mr->rangesize != 1) {
		printk("SNAT: multiple ranges no longer supported\n");
		return false;
	}
	return true;
}