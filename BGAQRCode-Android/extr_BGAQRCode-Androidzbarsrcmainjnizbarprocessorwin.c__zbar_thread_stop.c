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
struct TYPE_3__ {int /*<<< orphan*/  activity; int /*<<< orphan*/  notify; scalar_t__ running; scalar_t__ started; } ;
typedef  TYPE_1__ zbar_thread_t ;
typedef  int /*<<< orphan*/  zbar_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_event_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_event_trigger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_event_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int _zbar_thread_stop (zbar_thread_t *thr,
                       zbar_mutex_t *lock)
{
    if(thr->started) {
        thr->started = 0;
        _zbar_event_trigger(&thr->notify);
        while(thr->running)
            /* FIXME time out and abandon? */
            _zbar_event_wait(&thr->activity, lock, NULL);
        _zbar_event_destroy(&thr->notify);
        _zbar_event_destroy(&thr->activity);
    }
    return(0);
}