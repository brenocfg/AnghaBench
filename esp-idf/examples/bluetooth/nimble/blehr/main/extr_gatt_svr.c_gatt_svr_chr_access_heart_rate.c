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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct ble_gatt_access_ctxt {int /*<<< orphan*/  om; TYPE_1__* chr; } ;
typedef  int /*<<< orphan*/  body_sens_loc ;
struct TYPE_2__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int BLE_ATT_ERR_INSUFFICIENT_RES ; 
 int BLE_ATT_ERR_UNLIKELY ; 
 scalar_t__ GATT_HRS_BODY_SENSOR_LOC_UUID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ble_uuid_u16 (int /*<<< orphan*/ ) ; 
 int os_mbuf_append (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
gatt_svr_chr_access_heart_rate(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    /* Sensor location, set to "Chest" */
    static uint8_t body_sens_loc = 0x01;
    uint16_t uuid;
    int rc;

    uuid = ble_uuid_u16(ctxt->chr->uuid);

    if (uuid == GATT_HRS_BODY_SENSOR_LOC_UUID) {
        rc = os_mbuf_append(ctxt->om, &body_sens_loc, sizeof(body_sens_loc));

        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
    }

    assert(0);
    return BLE_ATT_ERR_UNLIKELY;
}