#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tp_flags; TYPE_2__* tp_active; int /*<<< orphan*/  tp_mutex; } ;
typedef  TYPE_1__ tpool_t ;
struct TYPE_5__ {scalar_t__ tpa_tid; struct TYPE_5__* tpa_next; } ;
typedef  TYPE_2__ tpool_active_t ;
typedef  scalar_t__ pthread_t ;

/* Variables and functions */
 int TP_WAIT ; 
 int /*<<< orphan*/  notify_waiters (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_self () ; 

__attribute__((used)) static void
job_cleanup(void *arg)
{
	tpool_t *tpool = arg;
	pthread_t my_tid = pthread_self();
	tpool_active_t *activep;
	tpool_active_t **activepp;

	pthread_mutex_lock(&tpool->tp_mutex);
	/* CSTYLED */
	for (activepp = &tpool->tp_active;; activepp = &activep->tpa_next) {
		activep = *activepp;
		if (activep->tpa_tid == my_tid) {
			*activepp = activep->tpa_next;
			break;
		}
	}
	if (tpool->tp_flags & TP_WAIT)
		notify_waiters(tpool);
}