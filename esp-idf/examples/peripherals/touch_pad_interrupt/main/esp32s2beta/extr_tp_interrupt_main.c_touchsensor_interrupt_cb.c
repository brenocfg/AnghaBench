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
struct TYPE_3__ {int intr_mask; int /*<<< orphan*/  pad_val; int /*<<< orphan*/  pad_num; int /*<<< orphan*/  pad_status; } ;
typedef  TYPE_1__ touch_event_t ;

/* Variables and functions */
 int TOUCH_PAD_INTR_MASK_DONE ; 
 int pdFALSE ; 
 int pdTRUE ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  que_touch ; 
 int /*<<< orphan*/  touch_pad_filter_baseline_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  touch_pad_get_scan_curr () ; 
 int /*<<< orphan*/  touch_pad_get_status () ; 
 int touch_pad_intr_status_get_mask () ; 
 int /*<<< orphan*/  xQueueSendFromISR (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 

__attribute__((used)) static void touchsensor_interrupt_cb(void *arg)
{
    int task_awoken = pdFALSE;
    touch_event_t evt;

    evt.intr_mask = touch_pad_intr_status_get_mask();
    evt.pad_status = touch_pad_get_status();
    evt.pad_num = touch_pad_get_scan_curr();

    if (evt.intr_mask & TOUCH_PAD_INTR_MASK_DONE) {
        touch_pad_filter_baseline_read(evt.pad_num, &evt.pad_val);
    }
    xQueueSendFromISR(que_touch, &evt, &task_awoken);
    if (task_awoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}