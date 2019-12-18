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
 int /*<<< orphan*/  HID_CONSUMER_VOLUME_DOWN ; 
 int /*<<< orphan*/  HID_CONSUMER_VOLUME_UP ; 
 int /*<<< orphan*/  HID_DEMO_TAG ; 
 int /*<<< orphan*/  esp_hidd_send_consumer_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hid_conn_id ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ sec_conn ; 
 int send_volum_up ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void hid_demo_task(void *pvParameters)
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    while(1) {
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        if (sec_conn) {
            ESP_LOGI(HID_DEMO_TAG, "Send the volume");
            send_volum_up = true;
            //uint8_t key_vaule = {HID_KEY_A};
            //esp_hidd_send_keyboard_value(hid_conn_id, 0, &key_vaule, 1);
            esp_hidd_send_consumer_value(hid_conn_id, HID_CONSUMER_VOLUME_UP, true);
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            if (send_volum_up) {
                send_volum_up = false;
                esp_hidd_send_consumer_value(hid_conn_id, HID_CONSUMER_VOLUME_UP, false);
                esp_hidd_send_consumer_value(hid_conn_id, HID_CONSUMER_VOLUME_DOWN, true);
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                esp_hidd_send_consumer_value(hid_conn_id, HID_CONSUMER_VOLUME_DOWN, false);
            }
        }
    }
}