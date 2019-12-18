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
struct nd_prefix {int /*<<< orphan*/  ndpr_genid; } ;
struct nd_pfxrouter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nd_pfxrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDPR_LOCK_ASSERT_HELD (struct nd_prefix*) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  ndprtr_zone ; 
 int /*<<< orphan*/  pfr_entry ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct nd_pfxrouter*) ; 

__attribute__((used)) static void
pfxrtr_del(struct nd_pfxrouter *pfr, struct nd_prefix *pr)
{
	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);
	NDPR_LOCK_ASSERT_HELD(pr);
	pr->ndpr_genid++;
	LIST_REMOVE(pfr, pfr_entry);
	zfree(ndprtr_zone, pfr);
}