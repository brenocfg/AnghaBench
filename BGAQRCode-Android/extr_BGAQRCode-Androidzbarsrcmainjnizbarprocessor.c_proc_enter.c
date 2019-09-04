#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int _zbar_processor_lock (TYPE_1__*) ; 

__attribute__((used)) static inline int proc_enter (zbar_processor_t *proc)
{
    _zbar_mutex_lock(&proc->mutex);
    return(_zbar_processor_lock(proc));
}