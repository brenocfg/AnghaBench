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

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TOUCHPAD_FILTER_TOUCH_PERIOD ; 
 int /*<<< orphan*/  TOUCH_FSM_MODE_TIMER ; 
 int /*<<< orphan*/  TOUCH_HVOLT_2V7 ; 
 int /*<<< orphan*/  TOUCH_HVOLT_ATTEN_1V ; 
 int /*<<< orphan*/  TOUCH_LVOLT_0V5 ; 
 int /*<<< orphan*/  touch_pad_filter_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_pad_init () ; 
 int /*<<< orphan*/  touch_pad_isr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  touch_pad_set_fsm_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_pad_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_example_read_task ; 
 int /*<<< orphan*/  tp_example_rtc_intr ; 
 int /*<<< orphan*/  tp_example_set_thresholds () ; 
 int /*<<< orphan*/  tp_example_touch_pad_init () ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void app_main(void)
{
    // Initialize touch pad peripheral, it will start a timer to run a filter
    ESP_LOGI(TAG, "Initializing touch pad");
    touch_pad_init();
    // If use interrupt trigger mode, should set touch sensor FSM mode at 'TOUCH_FSM_MODE_TIMER'.
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    // Set reference voltage for charging/discharging
    // For most usage scenarios, we recommend using the following combination:
    // the high reference valtage will be 2.7V - 1V = 1.7V, The low reference voltage will be 0.5V.
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    // Init touch pad IO
    tp_example_touch_pad_init();
    // Initialize and start a software filter to detect slight change of capacitance.
    touch_pad_filter_start(TOUCHPAD_FILTER_TOUCH_PERIOD);
    // Set thresh hold
    tp_example_set_thresholds();
    // Register touch interrupt ISR
    touch_pad_isr_register(tp_example_rtc_intr, NULL);
    // Start a task to show what pads have been touched
    xTaskCreate(&tp_example_read_task, "touch_pad_read_task", 2048, NULL, 5, NULL);
}