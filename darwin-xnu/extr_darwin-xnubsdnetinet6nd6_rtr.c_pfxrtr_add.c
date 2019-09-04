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
struct nd_prefix {int /*<<< orphan*/  ndpr_genid; int /*<<< orphan*/  ndpr_advrtrs; } ;
struct nd_pfxrouter {struct nd_defrouter* router; } ;
struct nd_defrouter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nd_pfxrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_LOCK_ASSERT_NOTHELD (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  bzero (struct nd_pfxrouter*,int) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  ndprtr_zone ; 
 int /*<<< orphan*/  pfr_entry ; 
 int /*<<< orphan*/  pfxlist_onlink_check () ; 
 struct nd_pfxrouter* zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfxrtr_add(struct nd_prefix *pr, struct nd_defrouter *dr)
{
	struct nd_pfxrouter *new;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);
	NDPR_LOCK_ASSERT_NOTHELD(pr);

	new = zalloc(ndprtr_zone);
	if (new == NULL)
		return;
	bzero(new, sizeof (*new));
	new->router = dr;

	NDPR_LOCK(pr);
	LIST_INSERT_HEAD(&pr->ndpr_advrtrs, new, pfr_entry);
	pr->ndpr_genid++;
	NDPR_UNLOCK(pr);

	pfxlist_onlink_check();
}