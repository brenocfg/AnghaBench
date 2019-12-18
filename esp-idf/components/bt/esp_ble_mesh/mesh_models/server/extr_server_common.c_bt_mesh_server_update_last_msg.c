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
typedef  int /*<<< orphan*/  u8_t ;
typedef  void* u16_t ;
struct bt_mesh_last_msg_info {int /*<<< orphan*/  timestamp; void* dst; void* src; int /*<<< orphan*/  tid; } ;
typedef  int /*<<< orphan*/  s64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_ADDR_IS_UNICAST (void*) ; 

void bt_mesh_server_update_last_msg(struct bt_mesh_last_msg_info *last,
                                    u8_t tid, u16_t src, u16_t dst, s64_t *now)
{
    /* Currently we only update msg info which dst is set to a unicast address */
    if (!BLE_MESH_ADDR_IS_UNICAST(dst)) {
        return;
    }

    last->tid = tid;
    last->src = src;
    last->dst = dst;
    last->timestamp = *now;
    return;
}