#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ app_gap_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_GAP_STATE_DEVICE_DISCOVERING ; 
 int /*<<< orphan*/  ESP_BT_CONNECTABLE ; 
 int /*<<< orphan*/  ESP_BT_GENERAL_DISCOVERABLE ; 
 int /*<<< orphan*/  ESP_BT_INQ_MODE_GENERAL_INQUIRY ; 
 int /*<<< orphan*/  bt_app_gap_cb ; 
 int /*<<< orphan*/  esp_bt_dev_set_device_name (char*) ; 
 int /*<<< orphan*/  esp_bt_gap_register_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_gap_set_scan_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_gap_start_discovery (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ m_dev_info ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void bt_app_gap_start_up(void)
{
    char *dev_name = "ESP_GAP_INQRUIY";
    esp_bt_dev_set_device_name(dev_name);

    /* set discoverable and connectable mode, wait to be connected */
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

    /* register GAP callback function */
    esp_bt_gap_register_callback(bt_app_gap_cb);

    /* inititialize device information and status */
    app_gap_cb_t *p_dev = &m_dev_info;
    memset(p_dev, 0, sizeof(app_gap_cb_t));

    /* start to discover nearby Bluetooth devices */
    p_dev->state = APP_GAP_STATE_DEVICE_DISCOVERING;
    esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
}