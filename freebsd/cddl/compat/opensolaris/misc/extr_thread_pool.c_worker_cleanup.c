#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tp_current; int tp_flags; int /*<<< orphan*/  tp_mutex; int /*<<< orphan*/  tp_busycv; } ;
typedef  TYPE_1__ tpool_t ;

/* Variables and functions */
 int TP_ABANDON ; 
 int TP_DESTROY ; 
 int /*<<< orphan*/  delete_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
worker_cleanup(void *arg)
{
	tpool_t *tpool = arg;

	if (--tpool->tp_current == 0 &&
	    (tpool->tp_flags & (TP_DESTROY | TP_ABANDON))) {
		if (tpool->tp_flags & TP_ABANDON) {
			pthread_mutex_unlock(&tpool->tp_mutex);
			delete_pool(tpool);
			return;
		}
		if (tpool->tp_flags & TP_DESTROY)
			(void) pthread_cond_broadcast(&tpool->tp_busycv);
	}
	pthread_mutex_unlock(&tpool->tp_mutex);
}