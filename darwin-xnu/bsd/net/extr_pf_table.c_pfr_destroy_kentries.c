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
struct pfr_kentryworkq {int dummy; } ;
struct pfr_kentry {int dummy; } ;

/* Variables and functions */
 struct pfr_kentry* SLIST_FIRST (struct pfr_kentryworkq*) ; 
 struct pfr_kentry* SLIST_NEXT (struct pfr_kentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_destroy_kentry (struct pfr_kentry*) ; 
 int /*<<< orphan*/  pfrke_workq ; 

__attribute__((used)) static void
pfr_destroy_kentries(struct pfr_kentryworkq *workq)
{
	struct pfr_kentry	*p, *q;

	for (p = SLIST_FIRST(workq); p != NULL; p = q) {
		q = SLIST_NEXT(p, pfrke_workq);
		pfr_destroy_kentry(p);
	}
}