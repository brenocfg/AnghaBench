#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  contol_point_handle; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  gattc_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommandIDPerformNotificationAction ; 
 int /*<<< orphan*/  ESP_GATT_AUTH_REQ_NONE ; 
 int /*<<< orphan*/  ESP_GATT_WRITE_TYPE_RSP ; 
 scalar_t__ ESP_NOTIFICATIONUID_LEN ; 
 size_t PROFILE_A_APP_ID ; 
 int /*<<< orphan*/  esp_ble_gattc_write_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gl_profile_tab ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void esp_perform_notification_action(uint8_t *notificationUID, uint8_t ActionID)
{
    uint8_t buffer[600] = {0};
    uint32_t index = 0;
    buffer[0] = CommandIDPerformNotificationAction;
    index ++;
    memcpy(&buffer[index], notificationUID, ESP_NOTIFICATIONUID_LEN);
    index += ESP_NOTIFICATIONUID_LEN;
    buffer[index] = ActionID;
    index ++;
    esp_ble_gattc_write_char( gl_profile_tab[PROFILE_A_APP_ID].gattc_if,
                              gl_profile_tab[PROFILE_A_APP_ID].conn_id,
                              gl_profile_tab[PROFILE_A_APP_ID].contol_point_handle,
                              index,
                              buffer,
                              ESP_GATT_WRITE_TYPE_RSP,
                              ESP_GATT_AUTH_REQ_NONE);
}