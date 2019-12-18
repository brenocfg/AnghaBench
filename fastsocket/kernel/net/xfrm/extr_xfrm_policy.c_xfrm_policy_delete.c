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
struct xfrm_policy {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct xfrm_policy* __xfrm_policy_unlink (struct xfrm_policy*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_policy_kill (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_policy_lock ; 

int xfrm_policy_delete(struct xfrm_policy *pol, int dir)
{
	write_lock_bh(&xfrm_policy_lock);
	pol = __xfrm_policy_unlink(pol, dir);
	write_unlock_bh(&xfrm_policy_lock);
	if (pol) {
		xfrm_policy_kill(pol);
		return 0;
	}
	return -ENOENT;
}