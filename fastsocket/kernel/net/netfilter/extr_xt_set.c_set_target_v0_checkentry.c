#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {struct xt_set_info_target_v0* targinfo; } ;
struct TYPE_3__ {scalar_t__* flags; } ;
struct TYPE_4__ {scalar_t__ index; TYPE_1__ u; } ;
struct xt_set_info_target_v0 {TYPE_2__ del_set; TYPE_2__ add_set; } ;
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 int IPSET_DIM_MAX ; 
 scalar_t__ IPSET_INVALID_ID ; 
 int /*<<< orphan*/  compat_flags (TYPE_2__*) ; 
 scalar_t__ ip_set_nfnl_get_byindex (scalar_t__) ; 
 int /*<<< orphan*/  ip_set_nfnl_put (scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 

__attribute__((used)) static bool
set_target_v0_checkentry(const struct xt_tgchk_param *par)
{
	struct xt_set_info_target_v0 *info = par->targinfo;
	ip_set_id_t index;

	if (info->add_set.index != IPSET_INVALID_ID) {
		index = ip_set_nfnl_get_byindex(info->add_set.index);
		if (index == IPSET_INVALID_ID) {
			pr_warning("Cannot find add_set index %u as target\n",
				   info->add_set.index);
			return false;
		}
	}

	if (info->del_set.index != IPSET_INVALID_ID) {
		index = ip_set_nfnl_get_byindex(info->del_set.index);
		if (index == IPSET_INVALID_ID) {
			pr_warning("Cannot find del_set index %u as target\n",
				   info->del_set.index);
			if (info->add_set.index != IPSET_INVALID_ID)
				ip_set_nfnl_put(info->add_set.index);
			return false;
		}
	}
	if (info->add_set.u.flags[IPSET_DIM_MAX-1] != 0 ||
	    info->del_set.u.flags[IPSET_DIM_MAX-1] != 0) {
		pr_warning("Protocol error: SET target dimension "
			   "is over the limit!\n");
		if (info->add_set.index != IPSET_INVALID_ID)
			ip_set_nfnl_put(info->add_set.index);
		if (info->del_set.index != IPSET_INVALID_ID)
			ip_set_nfnl_put(info->del_set.index);
		return false;
	}

	/* Fill out compatibility data */
	compat_flags(&info->add_set);
	compat_flags(&info->del_set);

	return true;
}