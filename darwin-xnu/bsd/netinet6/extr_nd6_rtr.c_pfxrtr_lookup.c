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
struct TYPE_2__ {struct nd_pfxrouter* lh_first; } ;
struct nd_prefix {TYPE_1__ ndpr_advrtrs; } ;
struct nd_pfxrouter {struct nd_defrouter* router; struct nd_pfxrouter* pfr_next; } ;
struct nd_defrouter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  NDPR_LOCK_ASSERT_HELD (struct nd_prefix*) ; 
 int /*<<< orphan*/  nd6_mutex ; 

__attribute__((used)) static struct nd_pfxrouter *
pfxrtr_lookup(struct nd_prefix *pr, struct nd_defrouter *dr)
{
	struct nd_pfxrouter *search;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);
	NDPR_LOCK_ASSERT_HELD(pr);

	for (search = pr->ndpr_advrtrs.lh_first; search;
	    search = search->pfr_next) {
		if (search->router == dr)
			break;
	}

	return (search);
}