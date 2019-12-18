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
struct xt_mtchk_param {struct ip6t_rt* matchinfo; } ;
struct ip6t_rt {int invflags; int flags; scalar_t__ rt_type; } ;

/* Variables and functions */
 int IP6T_RT_FST_MASK ; 
 int IP6T_RT_INV_MASK ; 
 int IP6T_RT_INV_TYP ; 
 int IP6T_RT_RES ; 
 int IP6T_RT_TYP ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static bool rt_mt6_check(const struct xt_mtchk_param *par)
{
	const struct ip6t_rt *rtinfo = par->matchinfo;

	if (rtinfo->invflags & ~IP6T_RT_INV_MASK) {
		pr_debug("ip6t_rt: unknown flags %X\n", rtinfo->invflags);
		return false;
	}
	if ((rtinfo->flags & (IP6T_RT_RES | IP6T_RT_FST_MASK)) &&
	    (!(rtinfo->flags & IP6T_RT_TYP) ||
	     (rtinfo->rt_type != 0) ||
	     (rtinfo->invflags & IP6T_RT_INV_TYP))) {
		pr_debug("`--rt-type 0' required before `--rt-0-*'");
		return false;
	}

	return true;
}