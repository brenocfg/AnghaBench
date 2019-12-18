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
struct xt_rateest {scalar_t__ refcnt; int /*<<< orphan*/  rstats; int /*<<< orphan*/  bstats; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xt_rateest*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xt_rateest_mutex ; 

void xt_rateest_put(struct xt_rateest *est)
{
	mutex_lock(&xt_rateest_mutex);
	if (--est->refcnt == 0) {
		hlist_del(&est->list);
		gen_kill_estimator(&est->bstats, &est->rstats);
		kfree(est);
	}
	mutex_unlock(&xt_rateest_mutex);
}