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
struct TYPE_4__ {int stop; scalar_t__ thread_handle; int /*<<< orphan*/  work_sem; } ;
typedef  TYPE_1__ osi_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_sem_give (int /*<<< orphan*/ *) ; 
 int osi_thread_join (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vTaskDelete (scalar_t__) ; 

__attribute__((used)) static void osi_thread_stop(osi_thread_t *thread)
{
    int ret;

    assert(thread != NULL);

    //stop the thread
    thread->stop = true;
    osi_sem_give(&thread->work_sem);

    //join
    ret = osi_thread_join(thread, 1000); //wait 1000ms
   
    //if join failed, delete the task here
    if (ret != 0 && thread->thread_handle) {
        vTaskDelete(thread->thread_handle);
    }
}