#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gatts_register_cb; } ;
struct TYPE_5__ {int handle; } ;
struct TYPE_6__ {int wr_desc_done; int /*<<< orphan*/  mtu; TYPE_1__ conn; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  BLE_ATT_MTU_DFLT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ble_att_set_preferred_mtu (int /*<<< orphan*/ ) ; 
 int ble_gatts_add_svcs (int /*<<< orphan*/ ) ; 
 int ble_gatts_count_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ble_gatts_start () ; 
 int /*<<< orphan*/  ble_gatts_svc_set_visibility (int /*<<< orphan*/ ,int) ; 
 TYPE_3__ ble_hs_cfg ; 
 int /*<<< orphan*/  ble_svc_gap_init () ; 
 int /*<<< orphan*/  ble_svc_gatt_init () ; 
 TYPE_2__* bt_mesh_gattc_info ; 
 int /*<<< orphan*/  gatt_register_cb ; 
 int /*<<< orphan*/  prov_svc_start_handle ; 
 int /*<<< orphan*/  proxy_svc_start_handle ; 
 int /*<<< orphan*/  svc_defs ; 

void bt_mesh_gatt_init(void)
{
    ble_att_set_preferred_mtu(BLE_ATT_MTU_DFLT);

    ble_hs_cfg.gatts_register_cb = gatt_register_cb;

#if defined(CONFIG_BLE_MESH_NODE) && CONFIG_BLE_MESH_NODE
    int rc;
    ble_svc_gap_init();
    ble_svc_gatt_init();

    rc = ble_gatts_count_cfg(svc_defs);
    assert(rc == 0);

    rc = ble_gatts_add_svcs(svc_defs);
    assert(rc == 0);

    ble_gatts_start();

    ble_gatts_svc_set_visibility(prov_svc_start_handle, 1);
    ble_gatts_svc_set_visibility(proxy_svc_start_handle, 0);
#endif

#if (CONFIG_BLE_MESH_PROVISIONER && CONFIG_BLE_MESH_PB_GATT) || \
    CONFIG_BLE_MESH_GATT_PROXY_CLIENT
    for (int i = 0; i < ARRAY_SIZE(bt_mesh_gattc_info); i++) {
        bt_mesh_gattc_info[i].conn.handle = 0xFFFF;
        bt_mesh_gattc_info[i].mtu = BLE_ATT_MTU_DFLT;
        bt_mesh_gattc_info[i].wr_desc_done = false;
    }
#endif
}