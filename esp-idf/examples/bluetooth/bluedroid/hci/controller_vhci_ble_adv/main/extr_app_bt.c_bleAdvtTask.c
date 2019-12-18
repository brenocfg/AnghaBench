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
 int esp_vhci_host_check_send_available () ; 
 int /*<<< orphan*/  esp_vhci_host_register_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_cmd_send_ble_adv_start () ; 
 int /*<<< orphan*/  hci_cmd_send_ble_set_adv_data () ; 
 int /*<<< orphan*/  hci_cmd_send_ble_set_adv_param () ; 
 int /*<<< orphan*/  hci_cmd_send_reset () ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vhci_host_cb ; 

void bleAdvtTask(void *pvParameters)
{
    int cmd_cnt = 0;
    bool send_avail = false;
    esp_vhci_host_register_callback(&vhci_host_cb);
    printf("BLE advt task start\n");
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        send_avail = esp_vhci_host_check_send_available();
        if (send_avail) {
            switch (cmd_cnt) {
            case 0: hci_cmd_send_reset(); ++cmd_cnt; break;
            case 1: hci_cmd_send_ble_set_adv_param(); ++cmd_cnt; break;
            case 2: hci_cmd_send_ble_set_adv_data(); ++cmd_cnt; break;
            case 3: hci_cmd_send_ble_adv_start(); ++cmd_cnt; break;
            }
        }
        printf("BLE Advertise, flag_send_avail: %d, cmd_sent: %d\n", send_avail, cmd_cnt);
    }
}