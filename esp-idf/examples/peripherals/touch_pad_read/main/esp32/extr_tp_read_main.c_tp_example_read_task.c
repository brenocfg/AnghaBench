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
typedef  int uint16_t ;

/* Variables and functions */
 int TOUCH_PAD_MAX ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  touch_pad_read (int,int*) ; 
 int /*<<< orphan*/  touch_pad_read_filtered (int,int*) ; 
 int /*<<< orphan*/  touch_pad_read_raw_data (int,int*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void tp_example_read_task(void *pvParameter)
{
    uint16_t touch_value;
    uint16_t touch_filter_value;
#if TOUCH_FILTER_MODE_EN
    printf("Touch Sensor filter mode read, the output format is: \nTouchpad num:[raw data, filtered data]\n\n");
#else
    printf("Touch Sensor normal mode read, the output format is: \nTouchpad num:[raw data]\n\n");
#endif
    while (1) {
        for (int i = 0; i < TOUCH_PAD_MAX; i++) {
#if TOUCH_FILTER_MODE_EN
            // If open the filter mode, please use this API to get the touch pad count.
            touch_pad_read_raw_data(i, &touch_value);
            touch_pad_read_filtered(i, &touch_filter_value);
            printf("T%d:[%4d,%4d] ", i, touch_value, touch_filter_value);
#else
            touch_pad_read(i, &touch_value);
            printf("T%d:[%4d] ", i, touch_value);
#endif
        }
        printf("\n");
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}