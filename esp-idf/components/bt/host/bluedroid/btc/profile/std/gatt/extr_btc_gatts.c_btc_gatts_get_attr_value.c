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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GetAttributeValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

esp_gatt_status_t btc_gatts_get_attr_value(uint16_t attr_handle, uint16_t *length, uint8_t **value)
{

     return BTA_GetAttributeValue(attr_handle, length, value);
}