#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct bt_mesh_send_cb {int dummy; } ;
struct TYPE_4__ {int relay; void* arg; } ;
typedef  TYPE_1__ bt_mesh_msg_t ;
struct TYPE_5__ {unsigned int busy; void* cb_data; struct bt_mesh_send_cb const* cb; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 TYPE_3__* BLE_MESH_ADV (struct net_buf*) ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_mesh_task_post (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ net_buf_ref (struct net_buf*) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 

void bt_mesh_adv_send(struct net_buf *buf, const struct bt_mesh_send_cb *cb,
                      void *cb_data)
{
    bt_mesh_msg_t msg = {
        .relay = false,
    };

    BT_DBG("type 0x%02x len %u: %s", BLE_MESH_ADV(buf)->type, buf->len,
           bt_hex(buf->data, buf->len));

    BLE_MESH_ADV(buf)->cb = cb;
    BLE_MESH_ADV(buf)->cb_data = cb_data;
    BLE_MESH_ADV(buf)->busy = 1U;

    msg.arg = (void *)net_buf_ref(buf);
    bt_mesh_task_post(&msg, portMAX_DELAY);
}