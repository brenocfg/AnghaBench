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
typedef  int uint_t ;
struct TYPE_4__ {int tp_minimum; int tp_maximum; int tp_linger; int /*<<< orphan*/  tp_attr; int /*<<< orphan*/  tp_waitcv; int /*<<< orphan*/  tp_workcv; int /*<<< orphan*/  tp_busycv; int /*<<< orphan*/  tp_mutex; } ;
typedef  TYPE_1__ tpool_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

tpool_t	*
tpool_create(uint_t min_threads, uint_t max_threads, uint_t linger,
	pthread_attr_t *attr)
{
	tpool_t	*tpool;
	int error;

	if (min_threads > max_threads || max_threads < 1) {
		errno = EINVAL;
		return (NULL);
	}

	tpool = calloc(1, sizeof (*tpool));
	if (tpool == NULL) {
		errno = ENOMEM;
		return (NULL);
	}
	(void) pthread_mutex_init(&tpool->tp_mutex, NULL);
	(void) pthread_cond_init(&tpool->tp_busycv, NULL);
	(void) pthread_cond_init(&tpool->tp_workcv, NULL);
	(void) pthread_cond_init(&tpool->tp_waitcv, NULL);
	tpool->tp_minimum = min_threads;
	tpool->tp_maximum = max_threads;
	tpool->tp_linger = linger;

	/* make all pool threads be detached daemon threads */
	(void) pthread_attr_init(&tpool->tp_attr);
	(void) pthread_attr_setdetachstate(&tpool->tp_attr,
	    PTHREAD_CREATE_DETACHED);

	return (tpool);
}