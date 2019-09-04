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
struct ifaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tqe_prev; int /*<<< orphan*/ * tqe_next; } ;
struct dadq {int dad_attached; TYPE_1__ dad_list; struct ifaddr* dad_ifa; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAD_LOCK (struct dadq*) ; 
 int /*<<< orphan*/  DAD_REMREF (struct dadq*) ; 
 int /*<<< orphan*/  DAD_UNLOCK (struct dadq*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct dadq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  dad6_mutex ; 
 int /*<<< orphan*/  dad_list ; 
 int /*<<< orphan*/  dadq ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nd6_dad_detach(struct dadq *dp, struct ifaddr *ifa)
{
	int detached;

	lck_mtx_lock(dad6_mutex);
	DAD_LOCK(dp);
	if ((detached = dp->dad_attached)) {
		VERIFY(dp->dad_ifa == ifa);
		TAILQ_REMOVE(&dadq, (struct dadq *)dp, dad_list);
		dp->dad_list.tqe_next = NULL;
		dp->dad_list.tqe_prev = NULL;
		dp->dad_attached = 0;
	}
	DAD_UNLOCK(dp);
	lck_mtx_unlock(dad6_mutex);
	if (detached) {
		DAD_REMREF(dp);		/* drop dadq_head reference */
	}
}