#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tp_attr; struct TYPE_5__* tpj_next; struct TYPE_5__* tp_head; } ;
typedef  TYPE_1__ tpool_t ;
typedef  TYPE_1__ tpool_job_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
delete_pool(tpool_t *tpool)
{
	tpool_job_t *job;

	/*
	 * There should be no pending jobs, but just in case...
	 */
	for (job = tpool->tp_head; job != NULL; job = tpool->tp_head) {
		tpool->tp_head = job->tpj_next;
		free(job);
	}
	(void) pthread_attr_destroy(&tpool->tp_attr);
	free(tpool);
}