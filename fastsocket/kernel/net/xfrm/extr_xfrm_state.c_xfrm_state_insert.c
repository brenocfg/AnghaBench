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
struct xfrm_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xfrm_state_bump_genids (struct xfrm_state*) ; 
 int /*<<< orphan*/  __xfrm_state_insert (struct xfrm_state*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_state_lock ; 

void xfrm_state_insert(struct xfrm_state *x)
{
	spin_lock_bh(&xfrm_state_lock);
	__xfrm_state_bump_genids(x);
	__xfrm_state_insert(x);
	spin_unlock_bh(&xfrm_state_lock);
}