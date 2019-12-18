#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tp_flags; scalar_t__ tp_idle; scalar_t__ tp_current; scalar_t__ tp_maximum; int /*<<< orphan*/  tp_mutex; int /*<<< orphan*/  tp_workcv; int /*<<< orphan*/  tp_njobs; TYPE_2__* tp_tail; TYPE_2__* tp_head; } ;
typedef  TYPE_1__ tpool_t ;
struct TYPE_7__ {void (* tpj_func ) (void*) ;struct TYPE_7__* tpj_next; void* tpj_arg; } ;
typedef  TYPE_2__ tpool_job_t ;

/* Variables and functions */
 int TP_SUSPEND ; 
 TYPE_2__* calloc (int,int) ; 
 scalar_t__ create_worker (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
tpool_dispatch(tpool_t *tpool, void (*func)(void *), void *arg)
{
	tpool_job_t *job;

	if ((job = calloc(1, sizeof (*job))) == NULL)
		return (-1);
	job->tpj_next = NULL;
	job->tpj_func = func;
	job->tpj_arg = arg;

	pthread_mutex_lock(&tpool->tp_mutex);

	if (tpool->tp_head == NULL)
		tpool->tp_head = job;
	else
		tpool->tp_tail->tpj_next = job;
	tpool->tp_tail = job;
	tpool->tp_njobs++;

	if (!(tpool->tp_flags & TP_SUSPEND)) {
		if (tpool->tp_idle > 0)
			(void) pthread_cond_signal(&tpool->tp_workcv);
		else if (tpool->tp_current < tpool->tp_maximum &&
		    create_worker(tpool) == 0)
			tpool->tp_current++;
	}

	pthread_mutex_unlock(&tpool->tp_mutex);
	return (0);
}