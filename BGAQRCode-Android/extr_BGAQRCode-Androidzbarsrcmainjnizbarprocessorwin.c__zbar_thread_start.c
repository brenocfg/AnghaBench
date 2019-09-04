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
struct TYPE_3__ {int started; int /*<<< orphan*/  activity; int /*<<< orphan*/  notify; scalar_t__ running; } ;
typedef  TYPE_1__ zbar_thread_t ;
typedef  int /*<<< orphan*/  zbar_thread_proc_t ;
typedef  int /*<<< orphan*/  zbar_mutex_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_event_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_event_init (int /*<<< orphan*/ *) ; 
 scalar_t__ _zbar_event_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int _zbar_thread_start (zbar_thread_t *thr,
                        zbar_thread_proc_t *proc,
                        void *arg,
                        zbar_mutex_t *lock)
{
    if(thr->started || thr->running)
        return(-1/*FIXME*/);
    thr->started = 1;
    _zbar_event_init(&thr->notify);
    _zbar_event_init(&thr->activity);

    HANDLE hthr = CreateThread(NULL, 0, proc, arg, 0, NULL);
    int rc = (!hthr ||
              _zbar_event_wait(&thr->activity, NULL, NULL) < 0 ||
              !thr->running);
    CloseHandle(hthr);
    if(rc) {
        thr->started = 0;
        _zbar_event_destroy(&thr->notify);
        _zbar_event_destroy(&thr->activity);
        return(-1/*FIXME*/);
    }
    return(0);
}