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
struct TYPE_3__ {scalar_t__ bar_numin; scalar_t__ bar_nthr; int /*<<< orphan*/  bar_lock; int /*<<< orphan*/  bar_sem; } ;
typedef  TYPE_1__ barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_wait (int /*<<< orphan*/ *) ; 

int
barrier_wait(barrier_t *bar)
{
	pthread_mutex_lock(&bar->bar_lock);

	if (++bar->bar_numin < bar->bar_nthr) {
		pthread_mutex_unlock(&bar->bar_lock);
#ifdef illumos
		sema_wait(&bar->bar_sem);
#else
		sem_wait(&bar->bar_sem);
#endif

		return (0);

	} else {
		int i;

		/* reset for next use */
		bar->bar_numin = 0;
		for (i = 1; i < bar->bar_nthr; i++)
#ifdef illumos
			sema_post(&bar->bar_sem);
#else
			sem_post(&bar->bar_sem);
#endif
		pthread_mutex_unlock(&bar->bar_lock);

		return (1);
	}
}