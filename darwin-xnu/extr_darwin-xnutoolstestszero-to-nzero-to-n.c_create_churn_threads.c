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
typedef  int uint32_t ;
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  SCHED_RR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  churn_thread ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int g_churn_count ; 
 scalar_t__ g_churn_pri ; 
 int /*<<< orphan*/ * g_churn_threads ; 
 int g_numcpus ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 int /*<<< orphan*/  pthread_attr_setschedpolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ valloc (int) ; 

__attribute__((used)) static void
create_churn_threads()
{
	if (g_churn_count == 0)
		g_churn_count = g_numcpus - 1;

	errno_t err;

	struct sched_param param = { .sched_priority = (int)g_churn_pri };
	pthread_attr_t attr;

	/* Array for churn threads */
	g_churn_threads = (pthread_t*) valloc(sizeof(pthread_t) * g_churn_count);
	assert(g_churn_threads);

	if ((err = pthread_attr_init(&attr)))
		errc(EX_OSERR, err, "pthread_attr_init");

	if ((err = pthread_attr_setschedparam(&attr, &param)))
		errc(EX_OSERR, err, "pthread_attr_setschedparam");

	if ((err = pthread_attr_setschedpolicy(&attr, SCHED_RR)))
		errc(EX_OSERR, err, "pthread_attr_setschedpolicy");

	for (uint32_t i = 0 ; i < g_churn_count ; i++) {
		pthread_t new_thread;

		if ((err = pthread_create(&new_thread, &attr, churn_thread, NULL)))
			errc(EX_OSERR, err, "pthread_create");
		g_churn_threads[i] = new_thread;
	}

	if ((err = pthread_attr_destroy(&attr)))
		errc(EX_OSERR, err, "pthread_attr_destroy");
}