#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  scanner; scalar_t__ streaming; scalar_t__ window; } ;
typedef  TYPE_1__ zbar_processor_t ;
typedef  int /*<<< orphan*/  zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int _zbar_process_image (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _zbar_processor_set_size (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_leave (TYPE_1__*) ; 
 int /*<<< orphan*/  zbar_image_get_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbar_image_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zbar_image_scanner_enable_cache (int /*<<< orphan*/ ,int) ; 

int zbar_process_image (zbar_processor_t *proc,
                        zbar_image_t *img)
{
    proc_enter(proc);
    _zbar_mutex_unlock(&proc->mutex);

    int rc = 0;
    if(img && proc->window)
        rc = _zbar_processor_set_size(proc,
                                      zbar_image_get_width(img),
                                      zbar_image_get_height(img));
    if(!rc) {
        zbar_image_scanner_enable_cache(proc->scanner, 0);
        rc = _zbar_process_image(proc, img);
        if(proc->streaming)
            zbar_image_scanner_enable_cache(proc->scanner, 1);
    }

    _zbar_mutex_lock(&proc->mutex);
    proc_leave(proc);
    return(rc);
}