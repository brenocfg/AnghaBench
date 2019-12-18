#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  handle; TYPE_1__* svc_def; } ;
struct ble_gatt_register_ctxt {scalar_t__ op; TYPE_2__ svc; } ;
struct TYPE_3__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 scalar_t__ BLE_GATT_REGISTER_OP_SVC ; 
 int /*<<< orphan*/  BLE_UUID16_DECLARE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_UUID_MESH_PROV_VAL ; 
 int /*<<< orphan*/  BT_UUID_MESH_PROXY_VAL ; 
 scalar_t__ ble_uuid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prov_svc_start_handle ; 
 int /*<<< orphan*/  proxy_svc_start_handle ; 

void gatt_register_cb(struct ble_gatt_register_ctxt *ctxt,
                      void *arg )
{
    if (ctxt->op == BLE_GATT_REGISTER_OP_SVC) {
        if (ble_uuid_cmp(ctxt->svc.svc_def->uuid, BLE_UUID16_DECLARE(BT_UUID_MESH_PROXY_VAL)) == 0) {
            proxy_svc_start_handle = ctxt->svc.handle;
        } else if (ble_uuid_cmp(ctxt->svc.svc_def->uuid, BLE_UUID16_DECLARE(BT_UUID_MESH_PROV_VAL)) == 0) {
            prov_svc_start_handle = ctxt->svc.handle;
        }
    }
}