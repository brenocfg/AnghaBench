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
struct protosw {int pr_flags; int /*<<< orphan*/  pr_usrreqs; struct protosw* pr_protosw; struct domain* pr_domain; } ;
struct domain {int /*<<< orphan*/  dom_protosw; } ;

/* Variables and functions */
 int PR_ATTACHED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct protosw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  domain_proto_mtx_lock_assert_held () ; 
 int /*<<< orphan*/  pr_entry ; 
 int /*<<< orphan*/  pru_sanitize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
attach_proto(struct protosw *pp, struct domain *dp)
{
	domain_proto_mtx_lock_assert_held();
	VERIFY(!(pp->pr_flags & PR_ATTACHED));
	VERIFY(pp->pr_domain == NULL);
	VERIFY(pp->pr_protosw == NULL);

	TAILQ_INSERT_TAIL(&dp->dom_protosw, pp, pr_entry);
	pp->pr_flags |= PR_ATTACHED;
	pp->pr_domain = dp;
	pp->pr_protosw = pp;

	/* do some cleaning up on user request callbacks */
	pru_sanitize(pp->pr_usrreqs);
}