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
struct net_buf {int /*<<< orphan*/  b; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct k_work {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  local_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_MESH_NET_IF_LOCAL ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ bt_mesh ; 
 int /*<<< orphan*/  bt_mesh_net_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_buf* net_buf_slist_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_buf_unref (struct net_buf*) ; 

__attribute__((used)) static void bt_mesh_net_local(struct k_work *work)
{
    struct net_buf *buf;

    while ((buf = net_buf_slist_get(&bt_mesh.local_queue))) {
        BT_DBG("len %u: %s", buf->len, bt_hex(buf->data, buf->len));
        bt_mesh_net_recv(&buf->b, 0, BLE_MESH_NET_IF_LOCAL);
        net_buf_unref(buf);
    }
}