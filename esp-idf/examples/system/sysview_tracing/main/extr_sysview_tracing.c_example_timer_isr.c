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
struct TYPE_2__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  group; int /*<<< orphan*/  count; int /*<<< orphan*/ * thnd; } ;
typedef  TYPE_1__ example_event_data_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSVIEW_EXAMPLE_SEND_EVENT_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSVIEW_EXAMPLE_SEND_EVENT_START () ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  eSetValueWithOverwrite ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdPASS ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  timer_group_enable_alarm_in_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_group_intr_clr_in_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xTaskNotifyFromISR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void example_timer_isr(void *arg)
{
    example_event_data_t *tim_arg = (example_event_data_t *)arg;

    if (tim_arg->thnd != NULL) {
        if (tim_arg->count++ < 10) {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            SYSVIEW_EXAMPLE_SEND_EVENT_START();
            if (xTaskNotifyFromISR(tim_arg->thnd, tim_arg->count, eSetValueWithOverwrite, &xHigherPriorityTaskWoken) != pdPASS) {
                ESP_EARLY_LOGE(TAG, "Failed to notify task %p", tim_arg->thnd);
            } else {
                SYSVIEW_EXAMPLE_SEND_EVENT_END(tim_arg->count);
                if (xHigherPriorityTaskWoken == pdTRUE) {
                    portYIELD_FROM_ISR();
                }
            }
        }
    }
    // re-start timer
    timer_group_intr_clr_in_isr(tim_arg->group, tim_arg->timer);
    timer_group_enable_alarm_in_isr(tim_arg->group, tim_arg->timer);
}