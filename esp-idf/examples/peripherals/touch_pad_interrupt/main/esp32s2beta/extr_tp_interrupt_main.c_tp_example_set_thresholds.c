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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TAG ; 
 int TOUCH_BUTTON_NUM ; 
 int /*<<< orphan*/ * button ; 
 int* button_threshold ; 
 int /*<<< orphan*/  touch_pad_read_raw_data (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  touch_pad_set_thresh (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tp_example_set_thresholds(void)
{
    uint32_t touch_value;
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        //read baseline value
        touch_pad_read_raw_data(button[i], &touch_value);
        //set interrupt threshold.
        touch_pad_set_thresh(button[i], touch_value * button_threshold[i]);
        ESP_LOGI(TAG, "test init: touch pad [%d] base %d, thresh %d", \
                 button[i], touch_value, (uint32_t)(touch_value * button_threshold[i]));
    }
}