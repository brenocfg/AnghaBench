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
struct xfrmk_spdinfo {int /*<<< orphan*/  spdhmcnt; int /*<<< orphan*/  spdhcnt; int /*<<< orphan*/  fwdscnt; int /*<<< orphan*/  outscnt; int /*<<< orphan*/  inscnt; int /*<<< orphan*/  fwdcnt; int /*<<< orphan*/  outcnt; int /*<<< orphan*/  incnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  policy_idx_hmask; int /*<<< orphan*/ * policy_count; } ;
struct TYPE_4__ {TYPE_1__ xfrm; } ;

/* Variables and functions */
 size_t XFRM_POLICY_FWD ; 
 size_t XFRM_POLICY_IN ; 
 size_t XFRM_POLICY_MAX ; 
 size_t XFRM_POLICY_OUT ; 
 TYPE_2__ init_net ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_policy_hashmax ; 
 int /*<<< orphan*/  xfrm_policy_lock ; 

void xfrm_spd_getinfo(struct xfrmk_spdinfo *si)
{
	read_lock_bh(&xfrm_policy_lock);
	si->incnt = init_net.xfrm.policy_count[XFRM_POLICY_IN];
	si->outcnt = init_net.xfrm.policy_count[XFRM_POLICY_OUT];
	si->fwdcnt = init_net.xfrm.policy_count[XFRM_POLICY_FWD];
	si->inscnt = init_net.xfrm.policy_count[XFRM_POLICY_IN+XFRM_POLICY_MAX];
	si->outscnt = init_net.xfrm.policy_count[XFRM_POLICY_OUT+XFRM_POLICY_MAX];
	si->fwdscnt = init_net.xfrm.policy_count[XFRM_POLICY_FWD+XFRM_POLICY_MAX];
	si->spdhcnt = init_net.xfrm.policy_idx_hmask;
	si->spdhmcnt = xfrm_policy_hashmax;
	read_unlock_bh(&xfrm_policy_lock);
}