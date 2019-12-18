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
struct seg_rx {scalar_t__ block; unsigned int seq_auth; unsigned int in_use; void* dst; void* src; int /*<<< orphan*/ * sub; int /*<<< orphan*/  seg_n; scalar_t__ obo; int /*<<< orphan*/  ack; } ;

/* Variables and functions */
 void* BLE_MESH_ADDR_UNASSIGNED ; 
 scalar_t__ BLOCK_COMPLETE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_DBG (char*,struct seg_rx*) ; 
 int /*<<< orphan*/  BT_WARN (char*) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_FRIEND ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_friend_clear_incomplete (int /*<<< orphan*/ *,void*,void*,unsigned int*) ; 
 int /*<<< orphan*/  k_delayed_work_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seg_rx_reset(struct seg_rx *rx, bool full_reset)
{
    BT_DBG("rx %p", rx);

    k_delayed_work_cancel(&rx->ack);

    if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND) && rx->obo &&
            rx->block != BLOCK_COMPLETE(rx->seg_n)) {
        BT_WARN("Clearing incomplete buffers from Friend queue");
        bt_mesh_friend_clear_incomplete(rx->sub, rx->src, rx->dst,
                                        &rx->seq_auth);
    }

    rx->in_use = 0U;

    /* We don't always reset these values since we need to be able to
     * send an ack if we receive a segment after we've already received
     * the full SDU.
     */
    if (full_reset) {
        rx->seq_auth = 0U;
        rx->sub = NULL;
        rx->src = BLE_MESH_ADDR_UNASSIGNED;
        rx->dst = BLE_MESH_ADDR_UNASSIGNED;
    }
}