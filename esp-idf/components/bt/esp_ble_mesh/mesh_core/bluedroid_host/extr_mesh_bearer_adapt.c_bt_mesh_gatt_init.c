#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  uuid128; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {TYPE_3__ uu; TYPE_2__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ tBT_UUID ;
struct TYPE_9__ {int handle; } ;
struct TYPE_13__ {int wr_desc_done; int /*<<< orphan*/  mtu; TYPE_1__ conn; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int BLE_MESH_GATTC_APP_UUID_BYTE ; 
 int /*<<< orphan*/  BTA_GATTC_AppRegister (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATTS_AppRegister (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATT_SetLocalMTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_DEF_BLE_MTU_SIZE ; 
 int /*<<< orphan*/  LEN_UUID_128 ; 
 int /*<<< orphan*/  bt_mesh_bta_gattc_cb ; 
 int /*<<< orphan*/  bt_mesh_bta_gatts_cb ; 
 TYPE_5__* bt_mesh_gattc_info ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void bt_mesh_gatt_init(void)
{
    tBT_UUID app_uuid = {LEN_UUID_128, {0}};

    BTA_GATT_SetLocalMTU(GATT_DEF_BLE_MTU_SIZE);

#if CONFIG_BLE_MESH_NODE
    /* Fill our internal UUID with a fixed pattern 0x96 for the ble mesh */
    memset(&app_uuid.uu.uuid128, 0x96, LEN_UUID_128);
    BTA_GATTS_AppRegister(&app_uuid, bt_mesh_bta_gatts_cb);
#endif

#if (CONFIG_BLE_MESH_PROVISIONER && CONFIG_BLE_MESH_PB_GATT) || \
    CONFIG_BLE_MESH_GATT_PROXY_CLIENT
    for (int i = 0; i < ARRAY_SIZE(bt_mesh_gattc_info); i++) {
        bt_mesh_gattc_info[i].conn.handle = 0xFFFF;
        bt_mesh_gattc_info[i].mtu = GATT_DEF_BLE_MTU_SIZE; /* Default MTU_SIZE 23 */
        bt_mesh_gattc_info[i].wr_desc_done = false;
    }
    memset(&app_uuid.uu.uuid128, BLE_MESH_GATTC_APP_UUID_BYTE, LEN_UUID_128);
    BTA_GATTC_AppRegister(&app_uuid, bt_mesh_bta_gattc_cb);
#endif
}