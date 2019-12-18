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
struct xfrmk_sadinfo {int /*<<< orphan*/  sadhmcnt; int /*<<< orphan*/  sadhcnt; int /*<<< orphan*/  sadcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  state_hmask; int /*<<< orphan*/  state_num; } ;
struct TYPE_4__ {TYPE_1__ xfrm; } ;

/* Variables and functions */
 TYPE_2__ init_net ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_state_hashmax ; 
 int /*<<< orphan*/  xfrm_state_lock ; 

void xfrm_sad_getinfo(struct xfrmk_sadinfo *si)
{
	spin_lock_bh(&xfrm_state_lock);
	si->sadcnt = init_net.xfrm.state_num;
	si->sadhcnt = init_net.xfrm.state_hmask;
	si->sadhmcnt = xfrm_state_hashmax;
	spin_unlock_bh(&xfrm_state_lock);
}