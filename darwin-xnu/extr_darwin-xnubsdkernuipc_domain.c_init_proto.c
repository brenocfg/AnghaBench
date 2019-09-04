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
struct protosw {int pr_flags; int /*<<< orphan*/  (* pr_init ) (struct protosw*,struct domain*) ;int /*<<< orphan*/  pr_filter_head; } ;
struct domain {int dummy; } ;

/* Variables and functions */
 int PR_ATTACHED ; 
 int PR_INITIALIZED ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  stub1 (struct protosw*,struct domain*) ; 

__attribute__((used)) static void
init_proto(struct protosw *pp, struct domain *dp)
{
	VERIFY(pp->pr_flags & PR_ATTACHED);

	if (!(pp->pr_flags & PR_INITIALIZED)) {
		TAILQ_INIT(&pp->pr_filter_head);
		if (pp->pr_init != NULL)
			pp->pr_init(pp, dp);
		pp->pr_flags |= PR_INITIALIZED;
	}
}