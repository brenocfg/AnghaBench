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
struct xt_tgchk_param {struct nf_nat_multi_range_compat* targinfo; } ;
struct nf_nat_multi_range_compat {int rangesize; TYPE_1__* range; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IP_NAT_RANGE_MAP_IPS ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static bool redirect_tg_check(const struct xt_tgchk_param *par)
{
	const struct nf_nat_multi_range_compat *mr = par->targinfo;

	if (mr->range[0].flags & IP_NAT_RANGE_MAP_IPS) {
		pr_debug("redirect_check: bad MAP_IPS.\n");
		return false;
	}
	if (mr->rangesize != 1) {
		pr_debug("redirect_check: bad rangesize %u.\n", mr->rangesize);
		return false;
	}
	return true;
}