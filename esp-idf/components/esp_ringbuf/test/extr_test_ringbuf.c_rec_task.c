#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ task_args_t ;
typedef  int /*<<< orphan*/  RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tasks_done ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 size_t xRingbufferGetMaxItemSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rec_task(void *args)
{
    RingbufHandle_t buffer = ((task_args_t *)args)->buffer;
    size_t max_rec_len = xRingbufferGetMaxItemSize(buffer);

    //Test receiving short length items
    read_from_buffer(buffer, ((task_args_t *)args)->type, 1);
    //Test receiving mid length items
    read_from_buffer(buffer, ((task_args_t *)args)->type, max_rec_len/2);
    //Test receiving long length items
    read_from_buffer(buffer, ((task_args_t *)args)->type, max_rec_len);

    xSemaphoreGive(tasks_done);
    vTaskDelete(NULL);
}