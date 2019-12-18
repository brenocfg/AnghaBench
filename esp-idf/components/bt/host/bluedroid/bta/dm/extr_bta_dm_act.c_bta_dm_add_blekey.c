#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_LE_KEY_VALUE ;
struct TYPE_4__ {int* bd_addr; int /*<<< orphan*/  key_type; int /*<<< orphan*/  blekey; } ;
struct TYPE_5__ {TYPE_1__ add_ble_key; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  BTM_SecAddBleKey (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bta_dm_add_blekey (tBTA_DM_MSG *p_data)
{
    if (!BTM_SecAddBleKey (p_data->add_ble_key.bd_addr,
                           (tBTM_LE_KEY_VALUE *)&p_data->add_ble_key.blekey,
                           p_data->add_ble_key.key_type)) {
        APPL_TRACE_ERROR ("BTA_DM: Error adding BLE Key for device %08x%04x",
                          (p_data->add_ble_key.bd_addr[0] << 24) + (p_data->add_ble_key.bd_addr[1] << 16) + \
                          (p_data->add_ble_key.bd_addr[2] << 8) + p_data->add_ble_key.bd_addr[3],
                          (p_data->add_ble_key.bd_addr[4] << 8) + p_data->add_ble_key.bd_addr[5]);
    }
}