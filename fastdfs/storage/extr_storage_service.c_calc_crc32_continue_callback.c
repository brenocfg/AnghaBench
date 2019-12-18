#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fast_task_info {scalar_t__ length; } ;

/* Variables and functions */
 int storage_dio_queue_push (struct fast_task_info*) ; 

__attribute__((used)) static int calc_crc32_continue_callback(struct fast_task_info *pTask)
{
    pTask->length = 0;
    return storage_dio_queue_push(pTask);
}