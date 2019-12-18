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
typedef  int /*<<< orphan*/  tBTA_DM_DISC ;
typedef  int /*<<< orphan*/  tBTA_DM_CONN ;
typedef  int esp_bt_discovery_mode_t ;
typedef  int esp_bt_connection_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_CONN ; 
 int /*<<< orphan*/  BTA_DM_GENERAL_DISC ; 
 int /*<<< orphan*/  BTA_DM_IGNORE ; 
 int /*<<< orphan*/  BTA_DM_LIMITED_DISC ; 
 int /*<<< orphan*/  BTA_DM_NON_CONN ; 
 int /*<<< orphan*/  BTA_DM_NON_DISC ; 
 int /*<<< orphan*/  BTA_DmSetVisibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTC_TRACE_WARNING (char*,int) ; 
#define  ESP_BT_CONNECTABLE 132 
#define  ESP_BT_GENERAL_DISCOVERABLE 131 
#define  ESP_BT_LIMITED_DISCOVERABLE 130 
#define  ESP_BT_NON_CONNECTABLE 129 
#define  ESP_BT_NON_DISCOVERABLE 128 

__attribute__((used)) static void btc_bt_set_scan_mode(esp_bt_connection_mode_t c_mode, esp_bt_discovery_mode_t d_mode)
{
    tBTA_DM_DISC disc_mode;
    tBTA_DM_CONN conn_mode;

    switch (c_mode) {
    case ESP_BT_NON_CONNECTABLE:
        conn_mode = BTA_DM_NON_CONN;
        break;
    case ESP_BT_CONNECTABLE:
        conn_mode = BTA_DM_CONN;
        break;
    default:
        BTC_TRACE_WARNING("invalid connection mode (0x%x)", c_mode);
        return;
    }

    switch (d_mode) {
    case ESP_BT_NON_DISCOVERABLE:
        disc_mode = BTA_DM_NON_DISC;
        break;
    case ESP_BT_LIMITED_DISCOVERABLE:
        disc_mode = BTA_DM_LIMITED_DISC;
        break;
    case ESP_BT_GENERAL_DISCOVERABLE:
        disc_mode = BTA_DM_GENERAL_DISC;
        break;
    default:
        BTC_TRACE_WARNING("invalid discovery mode (0x%x)", d_mode);
        return;
    }

    BTA_DmSetVisibility(disc_mode, conn_mode, BTA_DM_IGNORE, BTA_DM_IGNORE);
    return;
}