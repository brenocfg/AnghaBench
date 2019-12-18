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
struct TYPE_4__ {int* bd_addr; int /*<<< orphan*/  auth_mode; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  dev_type; } ;
struct TYPE_5__ {TYPE_1__ add_ble_device; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  BTM_SecAddBleDevice (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_add_ble_device (tBTA_DM_MSG *p_data)
{
    if (!BTM_SecAddBleDevice (p_data->add_ble_device.bd_addr, NULL,
                              p_data->add_ble_device.dev_type  ,
                              p_data->add_ble_device.addr_type,
                              p_data->add_ble_device.auth_mode)) {
        APPL_TRACE_ERROR ("BTA_DM: Error adding BLE Device for device %08x%04x",
                          (p_data->add_ble_device.bd_addr[0] << 24) + (p_data->add_ble_device.bd_addr[1] << 16) + \
                          (p_data->add_ble_device.bd_addr[2] << 8) + p_data->add_ble_device.bd_addr[3],
                          (p_data->add_ble_device.bd_addr[4] << 8) + p_data->add_ble_device.bd_addr[5]);
    }
}