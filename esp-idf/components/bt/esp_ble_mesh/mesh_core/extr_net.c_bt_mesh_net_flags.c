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
typedef  int u8_t ;
struct bt_mesh_subnet {scalar_t__ kr_flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_IVU_IN_PROGRESS ; 
 int BLE_MESH_NET_FLAG_IVU ; 
 int BLE_MESH_NET_FLAG_KR ; 
 TYPE_1__ bt_mesh ; 
 scalar_t__ bt_mesh_atomic_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8_t bt_mesh_net_flags(struct bt_mesh_subnet *sub)
{
    u8_t flags = 0x00;

    if (sub && sub->kr_flag) {
        flags |= BLE_MESH_NET_FLAG_KR;
    }

    if (bt_mesh_atomic_test_bit(bt_mesh.flags, BLE_MESH_IVU_IN_PROGRESS)) {
        flags |= BLE_MESH_NET_FLAG_IVU;
    }

    return flags;
}