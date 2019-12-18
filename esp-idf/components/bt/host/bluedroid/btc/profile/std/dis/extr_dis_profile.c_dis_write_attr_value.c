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
typedef  int /*<<< orphan*/  tGATT_WRITE_REQ ;
typedef  int /*<<< orphan*/  esp_gatt_status_t ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_GATT_OK ; 
 int /*<<< orphan*/  GATT_WRITE_NOT_PERMIT ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 

UINT8 dis_write_attr_value(tGATT_WRITE_REQ *p_data, esp_gatt_status_t *p_status)
{
    UNUSED(p_data);

    *p_status = GATT_WRITE_NOT_PERMIT;
    return ESP_GATT_OK;
}