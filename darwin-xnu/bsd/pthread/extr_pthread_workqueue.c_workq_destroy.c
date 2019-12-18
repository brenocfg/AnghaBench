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
struct workqueue {int /*<<< orphan*/  wq_lock; int /*<<< orphan*/  wq_turnstile; } ;
struct turnstile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct turnstile*) ; 
 int /*<<< orphan*/  lck_spin_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,int /*<<< orphan*/ *,struct turnstile**) ; 
 int /*<<< orphan*/  turnstile_deallocate (struct turnstile*) ; 
 int /*<<< orphan*/  workq_lck_grp ; 
 int /*<<< orphan*/  workq_zone_workqueue ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct workqueue*) ; 

void
workq_destroy(struct workqueue *wq)
{
	struct turnstile *ts;

	turnstile_complete((uintptr_t)wq, &wq->wq_turnstile, &ts);
	assert(ts);
	turnstile_cleanup();
	turnstile_deallocate(ts);

	lck_spin_destroy(&wq->wq_lock, workq_lck_grp);
	zfree(workq_zone_workqueue, wq);
}