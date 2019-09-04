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
struct sigevent {int sigev_notify; int /*<<< orphan*/  sigev_value; int /*<<< orphan*/  (* sigev_notify_function ) (int /*<<< orphan*/ ) ;} ;
struct lio_state {struct sigevent* sev; } ;

/* Variables and functions */
#define  SIGEV_SIGNAL 129 
#define  SIGEV_THREAD 128 
 int /*<<< orphan*/  free (struct lio_state*) ; 
 int /*<<< orphan*/  lio_wait (struct lio_state*) ; 
 int /*<<< orphan*/  notify_signal (struct sigevent*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *wait_thread(void *p)
{
	struct lio_state *st = p;
	struct sigevent *sev = st->sev;
	lio_wait(st);
	free(st);
	switch (sev->sigev_notify) {
	case SIGEV_SIGNAL:
		notify_signal(sev);
		break;
	case SIGEV_THREAD:
		sev->sigev_notify_function(sev->sigev_value);
		break;
	}
	return 0;
}