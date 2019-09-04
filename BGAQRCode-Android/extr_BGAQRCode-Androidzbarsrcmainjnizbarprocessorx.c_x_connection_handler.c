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
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_processor_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  _zbar_processor_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_handle_events (TYPE_1__*) ; 

__attribute__((used)) static int x_connection_handler (zbar_processor_t *proc,
                                 int i)
{
    _zbar_mutex_lock(&proc->mutex);
    _zbar_processor_lock(proc);
    _zbar_mutex_unlock(&proc->mutex);

    x_handle_events(proc);

    _zbar_mutex_lock(&proc->mutex);
    _zbar_processor_unlock(proc, 0);
    _zbar_mutex_unlock(&proc->mutex);
    return(0);
}