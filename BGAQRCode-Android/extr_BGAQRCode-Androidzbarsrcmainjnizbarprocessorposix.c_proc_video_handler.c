#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  video; scalar_t__ streaming; } ;
typedef  TYPE_1__ zbar_processor_t ;
typedef  int /*<<< orphan*/  zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_process_image (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_processor_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  _zbar_processor_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zbar_image_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zbar_video_next_image (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_video_handler (zbar_processor_t *proc,
                               int i)
{
    _zbar_mutex_lock(&proc->mutex);
    _zbar_processor_lock(proc);
    _zbar_mutex_unlock(&proc->mutex);

    zbar_image_t *img = NULL;
    if(proc->streaming) {
        /* not expected to block */
        img = zbar_video_next_image(proc->video);
        if(img)
            _zbar_process_image(proc, img);
    }

    _zbar_mutex_lock(&proc->mutex);
    _zbar_processor_unlock(proc, 0);
    _zbar_mutex_unlock(&proc->mutex);
    if(img)
        zbar_image_destroy(img);
    return(0);
}