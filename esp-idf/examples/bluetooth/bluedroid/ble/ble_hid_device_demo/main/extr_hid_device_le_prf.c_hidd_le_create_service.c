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
typedef  int /*<<< orphan*/  esp_gatt_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAS_IDX_NB ; 
 int /*<<< orphan*/  bas_att_db ; 
 int /*<<< orphan*/  esp_ble_gatts_create_attr_tab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hidd_le_create_service(esp_gatt_if_t gatts_if)
{
    /* Here should added the battery service first, because the hid service should include the battery service.
       After finish to added the battery service then can added the hid service. */
    esp_ble_gatts_create_attr_tab(bas_att_db, gatts_if, BAS_IDX_NB, 0);

}