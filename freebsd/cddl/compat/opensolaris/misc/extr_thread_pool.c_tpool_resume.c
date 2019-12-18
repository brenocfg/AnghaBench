#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tp_flags; int tp_njobs; int tp_idle; scalar_t__ tp_current; scalar_t__ tp_maximum; int /*<<< orphan*/  tp_mutex; int /*<<< orphan*/  tp_workcv; } ;
typedef  TYPE_1__ tpool_t ;

/* Variables and functions */
 int TP_SUSPEND ; 
 scalar_t__ create_worker (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
tpool_resume(tpool_t *tpool)
{
	int excess;

	pthread_mutex_lock(&tpool->tp_mutex);
	if (!(tpool->tp_flags & TP_SUSPEND)) {
		pthread_mutex_unlock(&tpool->tp_mutex);
		return;
	}
	tpool->tp_flags &= ~TP_SUSPEND;
	(void) pthread_cond_broadcast(&tpool->tp_workcv);
	excess = tpool->tp_njobs - tpool->tp_idle;
	while (excess-- > 0 && tpool->tp_current < tpool->tp_maximum) {
		if (create_worker(tpool) != 0)
			break;		/* pthread_create() failed */
		tpool->tp_current++;
	}
	pthread_mutex_unlock(&tpool->tp_mutex);
}