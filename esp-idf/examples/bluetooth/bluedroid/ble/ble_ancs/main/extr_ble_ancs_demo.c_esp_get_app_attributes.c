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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  contol_point_handle; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  gattc_if; } ;

/* Variables and functions */
 size_t CommandIDGetAppAttributes ; 
 int /*<<< orphan*/  ESP_GATT_AUTH_REQ_NONE ; 
 int /*<<< orphan*/  ESP_GATT_WRITE_TYPE_RSP ; 
 size_t PROFILE_A_APP_ID ; 
 int /*<<< orphan*/  esp_ble_gattc_write_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gl_profile_tab ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,size_t) ; 

void esp_get_app_attributes(uint8_t *appidentifier, uint16_t appidentifier_len, uint8_t num_attr, uint8_t *p_app_attrs)
{
    uint8_t buffer[600] = {0};
    uint32_t index = 0;
    buffer[0] = CommandIDGetAppAttributes;
    index ++;
    memcpy(&buffer[index], appidentifier, appidentifier_len);
    index += appidentifier_len;
    memcpy(&buffer[index], p_app_attrs, num_attr);
    index += num_attr;

    esp_ble_gattc_write_char( gl_profile_tab[PROFILE_A_APP_ID].gattc_if,
                              gl_profile_tab[PROFILE_A_APP_ID].conn_id,
                              gl_profile_tab[PROFILE_A_APP_ID].contol_point_handle,
                              index,
                              buffer,
                              ESP_GATT_WRITE_TYPE_RSP,
                              ESP_GATT_AUTH_REQ_NONE);
}