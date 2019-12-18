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
 int TOUCH_BUTTON_NUM ; 
 int* button ; 
 int portTICK_PERIOD_MS ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  touch_pad_read_raw_data (int,int*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void tp_example_read_task(void *pvParameter)
{
    uint32_t touch_value;
    
    /* Wait touch sensor init done */
    vTaskDelay(100 / portTICK_RATE_MS);
    printf("Touch Sensor read, the output format is: \nTouchpad num:[raw data]\n\n");

    while (1) {
        for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
            touch_pad_read_raw_data(button[i], &touch_value);    // read raw data.
            printf("T%d: [%4d] ", button[i], touch_value);
        }
        printf("\n");
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}