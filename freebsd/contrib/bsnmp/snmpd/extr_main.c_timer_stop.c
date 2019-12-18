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
struct timer {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int evClearTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evctx ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  poll_stop_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void
timer_stop(void *p)
{
	struct timer *tp = p;

	LIST_REMOVE(tp, link);
#ifdef USE_LIBBEGEMOT
	poll_stop_timer(tp->id);
#else
	if (evClearTimer(evctx, tp->id) == -1) {
		syslog(LOG_ERR, "cannot stop timer: %m");
		exit(1);
	}
#endif
	free(p);
}