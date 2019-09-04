#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  qlock; TYPE_3__* state; } ;
typedef  TYPE_1__ zbar_video_t ;
struct TYPE_6__ {int /*<<< orphan*/  activity; scalar_t__ running; int /*<<< orphan*/  notify; scalar_t__ started; } ;
typedef  TYPE_2__ zbar_thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  hwnd; TYPE_2__ thread; } ;
typedef  TYPE_3__ video_state_t ;
typedef  int /*<<< orphan*/  ZTHREAD ;
typedef  int /*<<< orphan*/  MSG ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int MsgWaitForMultipleObjects (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PM_NOYIELD ; 
 int PM_REMOVE ; 
 scalar_t__ PeekMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QS_ALLINPUT ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  _zbar_event_trigger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_thread_init (TYPE_2__*) ; 
 int /*<<< orphan*/  _zbar_thread_self () ; 
 int /*<<< orphan*/  capCreateCaptureWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprintf (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ZTHREAD vfw_capture_thread (void *arg)
{
    zbar_video_t *vdo = arg;
    video_state_t *state = vdo->state;
    zbar_thread_t *thr = &state->thread;

    state->hwnd = capCreateCaptureWindow(NULL, WS_POPUP, 0, 0, 1, 1, NULL, 0);
    if(!state->hwnd)
        goto done;

    _zbar_mutex_lock(&vdo->qlock);
    _zbar_thread_init(thr);
    zprintf(4, "spawned vfw capture thread (thr=%04lx)\n",
            _zbar_thread_self());

    MSG msg;
    int rc = 0;
    while(thr->started && rc >= 0 && rc <= 1) {
        _zbar_mutex_unlock(&vdo->qlock);

        rc = MsgWaitForMultipleObjects(1, &thr->notify, 0,
                                       INFINITE, QS_ALLINPUT);
        if(rc == 1)
            while(PeekMessage(&msg, NULL, 0, 0, PM_NOYIELD | PM_REMOVE))
                if(rc > 0) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }

        _zbar_mutex_lock(&vdo->qlock);
    }

 done:
    thr->running = 0;
    _zbar_event_trigger(&thr->activity);
    _zbar_mutex_unlock(&vdo->qlock);
    return(0);
}