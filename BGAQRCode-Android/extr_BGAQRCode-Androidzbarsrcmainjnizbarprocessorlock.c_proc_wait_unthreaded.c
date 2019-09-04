#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_timer_t ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  video; scalar_t__ streaming; } ;
typedef  TYPE_1__ zbar_processor_t ;
typedef  int /*<<< orphan*/  zbar_image_t ;
struct TYPE_8__ {int events; } ;
typedef  TYPE_2__ proc_waiter_t ;

/* Variables and functions */
 int EVENTS_PENDING ; 
 int MAX_INPUT_BLOCK ; 
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_process_image (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _zbar_processor_input_wait (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int _zbar_timer_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbar_image_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ zbar_video_get_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zbar_video_next_image (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int proc_wait_unthreaded (zbar_processor_t *proc,
                                        proc_waiter_t *waiter,
                                        zbar_timer_t *timeout)
{
    int blocking = proc->streaming && zbar_video_get_fd(proc->video) < 0;
    _zbar_mutex_unlock(&proc->mutex);

    int rc = 1;
    while(rc > 0 && (waiter->events & EVENTS_PENDING)) {
        /* FIXME lax w/the locking (though shouldn't matter...) */
        if(blocking) {
            zbar_image_t *img = zbar_video_next_image(proc->video);
            if(!img) {
                rc = -1;
                break;
            }

            /* FIXME reacquire API lock! (refactor w/video thread?) */
            _zbar_mutex_lock(&proc->mutex);
            _zbar_process_image(proc, img);
            zbar_image_destroy(img);
            _zbar_mutex_unlock(&proc->mutex);
        }
        int reltime = _zbar_timer_check(timeout);
        if(blocking && (reltime < 0 || reltime > MAX_INPUT_BLOCK))
            reltime = MAX_INPUT_BLOCK;
        rc = _zbar_processor_input_wait(proc, NULL, reltime);
    }
    _zbar_mutex_lock(&proc->mutex);
    return(rc);
}