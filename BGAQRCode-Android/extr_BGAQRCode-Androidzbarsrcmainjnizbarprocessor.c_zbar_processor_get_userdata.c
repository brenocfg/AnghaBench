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
struct TYPE_3__ {int /*<<< orphan*/  mutex; scalar_t__ userdata; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 

void *zbar_processor_get_userdata (const zbar_processor_t *proc)
{
    zbar_processor_t *ncproc = (zbar_processor_t*)proc;
    _zbar_mutex_lock(&ncproc->mutex);
    void *userdata = (void*)ncproc->userdata;
    _zbar_mutex_unlock(&ncproc->mutex);
    return(userdata);
}