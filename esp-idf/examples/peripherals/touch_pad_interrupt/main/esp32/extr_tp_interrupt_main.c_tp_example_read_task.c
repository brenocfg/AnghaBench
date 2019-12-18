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
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int TOUCH_PAD_MAX ; 
 int TOUCH_THRESH_PERCENT ; 
 int portTICK_PERIOD_MS ; 
 int* s_pad_activated ; 
 int* s_pad_init_val ; 
 int /*<<< orphan*/  touch_pad_clear_status () ; 
 int /*<<< orphan*/  touch_pad_intr_disable () ; 
 int /*<<< orphan*/  touch_pad_intr_enable () ; 
 int /*<<< orphan*/  touch_pad_read_filtered (int,int*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void tp_example_read_task(void *pvParameter)
{
    static int show_message;
    int change_mode = 0;
    int filter_mode = 0;
    while (1) {
        if (filter_mode == 0) {
            //interrupt mode, enable touch interrupt
            touch_pad_intr_enable();
            for (int i = 0; i < TOUCH_PAD_MAX; i++) {
                if (s_pad_activated[i] == true) {
                    ESP_LOGI(TAG, "T%d activated!", i);
                    // Wait a while for the pad being released
                    vTaskDelay(200 / portTICK_PERIOD_MS);
                    // Clear information on pad activation
                    s_pad_activated[i] = false;
                    // Reset the counter triggering a message
                    // that application is running
                    show_message = 1;
                }
            }
        } else {
            //filter mode, disable touch interrupt
            touch_pad_intr_disable();
            touch_pad_clear_status();
            for (int i = 0; i < TOUCH_PAD_MAX; i++) {
                uint16_t value = 0;
                touch_pad_read_filtered(i, &value);
                if (value < s_pad_init_val[i] * TOUCH_THRESH_PERCENT / 100) {
                    ESP_LOGI(TAG, "T%d activated!", i);
                    ESP_LOGI(TAG, "value: %d; init val: %d", value, s_pad_init_val[i]);
                    vTaskDelay(200 / portTICK_PERIOD_MS);
                    // Reset the counter to stop changing mode.
                    change_mode = 1;
                    show_message = 1;
                }
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);

        // If no pad is touched, every couple of seconds, show a message
        // that application is running
        if (show_message++ % 500 == 0) {
            ESP_LOGI(TAG, "Waiting for any pad being touched...");
        }
        // Change mode if no pad is touched for a long time.
        // We can compare the two different mode.
        if (change_mode++ % 2000 == 0) {
            filter_mode = !filter_mode;
            ESP_LOGW(TAG, "Change mode...%s", filter_mode == 0 ? "interrupt mode" : "filter mode");
        }
    }
}