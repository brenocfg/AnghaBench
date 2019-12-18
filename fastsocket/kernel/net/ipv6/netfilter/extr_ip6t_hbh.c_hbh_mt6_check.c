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
struct xt_mtchk_param {struct ip6t_opts* matchinfo; } ;
struct ip6t_opts {int invflags; int flags; } ;

/* Variables and functions */
 int IP6T_OPTS_INV_MASK ; 
 int IP6T_OPTS_NSTRICT ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static bool hbh_mt6_check(const struct xt_mtchk_param *par)
{
	const struct ip6t_opts *optsinfo = par->matchinfo;

	if (optsinfo->invflags & ~IP6T_OPTS_INV_MASK) {
		pr_debug("ip6t_opts: unknown flags %X\n", optsinfo->invflags);
		return false;
	}

	if (optsinfo->flags & IP6T_OPTS_NSTRICT) {
		pr_debug("ip6t_opts: Not strict - not implemented");
		return false;
	}

	return true;
}