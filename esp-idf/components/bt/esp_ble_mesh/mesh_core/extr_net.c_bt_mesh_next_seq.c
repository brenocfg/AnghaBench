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
typedef  int /*<<< orphan*/  u32_t ;
struct TYPE_2__ {scalar_t__ seq; scalar_t__ iv_index; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_IVU_IN_PROGRESS ; 
 int /*<<< orphan*/  BLE_MESH_KEY_PRIMARY ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_SETTINGS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IV_UPDATE_SEQ_LIMIT ; 
 TYPE_1__ bt_mesh ; 
 int /*<<< orphan*/  bt_mesh_atomic_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_beacon_ivu_initiator (int) ; 
 int /*<<< orphan*/  bt_mesh_net_iv_update (scalar_t__,int) ; 
 int /*<<< orphan*/  bt_mesh_net_sec_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_mesh_store_seq () ; 
 scalar_t__ bt_mesh_subnet_get (int /*<<< orphan*/ ) ; 

u32_t bt_mesh_next_seq(void)
{
    u32_t seq = bt_mesh.seq++;

    if (IS_ENABLED(CONFIG_BLE_MESH_SETTINGS)) {
        bt_mesh_store_seq();
    }

    if (!bt_mesh_atomic_test_bit(bt_mesh.flags, BLE_MESH_IVU_IN_PROGRESS) &&
            bt_mesh.seq > IV_UPDATE_SEQ_LIMIT &&
            bt_mesh_subnet_get(BLE_MESH_KEY_PRIMARY)) {
#if CONFIG_BLE_MESH_NODE
        bt_mesh_beacon_ivu_initiator(true);
#endif
        bt_mesh_net_iv_update(bt_mesh.iv_index + 1, true);
        bt_mesh_net_sec_update(NULL);
    }

    return seq;
}