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
struct TYPE_4__ {int /*<<< orphan*/  tp_attr; } ;
typedef  TYPE_1__ tpool_t ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpool_worker ; 

__attribute__((used)) static int
create_worker(tpool_t *tpool)
{
	sigset_t maskset, oset;
	pthread_t thread;
	int error;

	sigfillset(&maskset);
	(void) pthread_sigmask(SIG_SETMASK, &maskset, &oset);
	error = pthread_create(&thread, &tpool->tp_attr, tpool_worker, tpool);
	(void) pthread_sigmask(SIG_SETMASK, &oset, NULL);
	return (error);
}