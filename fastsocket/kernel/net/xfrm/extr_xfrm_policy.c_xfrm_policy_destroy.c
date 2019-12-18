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
struct TYPE_2__ {int /*<<< orphan*/  dead; } ;
struct xfrm_policy {int /*<<< orphan*/  security; int /*<<< orphan*/  timer; TYPE_1__ walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xfrm_policy*) ; 
 int /*<<< orphan*/  security_xfrm_policy_free (int /*<<< orphan*/ ) ; 

void xfrm_policy_destroy(struct xfrm_policy *policy)
{
	BUG_ON(!policy->walk.dead);

	if (del_timer(&policy->timer))
		BUG();

	security_xfrm_policy_free(policy->security);
	kfree(policy);
}