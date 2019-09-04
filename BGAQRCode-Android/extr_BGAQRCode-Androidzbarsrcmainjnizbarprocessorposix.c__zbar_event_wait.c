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
typedef  int /*<<< orphan*/  zbar_timer_t ;
typedef  int /*<<< orphan*/  zbar_mutex_t ;
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ zbar_event_t ;

/* Variables and functions */
 int _zbar_timer_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_sleep (int) ; 

int _zbar_event_wait (zbar_event_t *event,
                      zbar_mutex_t *lock,
                      zbar_timer_t *timeout)
{
    int rc = !event->state;
    if(rc) {
        if(!timeout)
            /* FIXME was that error or hang? */
            return(-1);

        int sleep = _zbar_timer_check(timeout);
        if(sleep)
            proc_sleep(sleep);
    }

    rc = !event->state;

    /* consume/reset event */
    event->state = 0;

    return(rc);
}