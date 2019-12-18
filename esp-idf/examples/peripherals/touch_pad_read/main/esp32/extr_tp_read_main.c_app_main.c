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
 int /*<<< orphan*/  TOUCHPAD_FILTER_TOUCH_PERIOD ; 
 int /*<<< orphan*/  TOUCH_HVOLT_2V7 ; 
 int /*<<< orphan*/  TOUCH_HVOLT_ATTEN_1V ; 
 int /*<<< orphan*/  TOUCH_LVOLT_0V5 ; 
 int /*<<< orphan*/  touch_pad_filter_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_pad_init () ; 
 int /*<<< orphan*/  touch_pad_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_example_read_task ; 
 int /*<<< orphan*/  tp_example_touch_pad_init () ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void app_main(void)
{
    // Initialize touch pad peripheral.
    // The default fsm mode is software trigger mode.
    touch_pad_init();
    // Set reference voltage for charging/discharging
    // In this case, the high reference valtage will be 2.7V - 1V = 1.7V
    // The low reference voltage will be 0.5
    // The larger the range, the larger the pulse count value.
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    tp_example_touch_pad_init();
#if TOUCH_FILTER_MODE_EN
    touch_pad_filter_start(TOUCHPAD_FILTER_TOUCH_PERIOD);
#endif
    // Start task to read values sensed by pads
    xTaskCreate(&tp_example_read_task, "touch_pad_read_task", 2048, NULL, 5, NULL);
}