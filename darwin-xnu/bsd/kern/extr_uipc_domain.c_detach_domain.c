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
struct domain_old {int /*<<< orphan*/ * dom_mtx; int /*<<< orphan*/ * dom_next; } ;
struct domain {int dom_flags; struct domain_old* dom_old; } ;

/* Variables and functions */
 int DOM_ATTACHED ; 
 int DOM_OLD ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  dom_entry ; 
 int /*<<< orphan*/  domain_proto_mtx_lock_assert_held () ; 
 int /*<<< orphan*/  domains ; 

__attribute__((used)) static void
detach_domain(struct domain *dp)
{
	domain_proto_mtx_lock_assert_held();
	VERIFY(dp->dom_flags & DOM_ATTACHED);

	TAILQ_REMOVE(&domains, dp, dom_entry);
	dp->dom_flags &= ~DOM_ATTACHED;

	if (dp->dom_flags & DOM_OLD) {
		struct domain_old *odp = dp->dom_old;

		VERIFY(odp != NULL);
		odp->dom_next = NULL;
		odp->dom_mtx = NULL;
	}
}