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
struct TYPE_3__ {int bar_nthr; scalar_t__ bar_numin; int /*<<< orphan*/  bar_sem; int /*<<< orphan*/  bar_lock; } ;
typedef  TYPE_1__ barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  USYNC_THREAD ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
barrier_init(barrier_t *bar, int nthreads)
{
	pthread_mutex_init(&bar->bar_lock, NULL);
#ifdef illumos
	sema_init(&bar->bar_sem, 0, USYNC_THREAD, NULL);
#else
	sem_init(&bar->bar_sem, 0, 0);
#endif

	bar->bar_numin = 0;
	bar->bar_nthr = nthreads;
}