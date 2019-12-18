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
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGMADELTA_CHANNEL_0 ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  sigmadelta_example_init () ; 
 int /*<<< orphan*/  sigmadelta_set_duty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void app_main(void)
{
    sigmadelta_example_init();

    int8_t duty = 0;
    int inc = 1;
    while (1) {
        sigmadelta_set_duty(SIGMADELTA_CHANNEL_0, duty);
        /* By changing delay time, you can change the blink frequency of LED */
        vTaskDelay(10 / portTICK_PERIOD_MS);

        duty += inc;
        if (duty == 127 || duty == -127) {
            inc = (-1) * inc;
        }
    }
}