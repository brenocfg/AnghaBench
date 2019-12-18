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
struct net_buf {int /*<<< orphan*/  b; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct bt_mesh_send_cb {int /*<<< orphan*/  (* end ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* start ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
struct bt_mesh_net_tx {TYPE_1__* ctx; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_work; int /*<<< orphan*/  local_queue; int /*<<< orphan*/  seq; } ;
struct TYPE_3__ {unsigned int send_ttl; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ BLE_MESH_ADDR_IS_UNICAST (int /*<<< orphan*/ ) ; 
 unsigned int BLE_MESH_TTL_DEFAULT ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_GATT_PROXY_SERVER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ bt_mesh ; 
 int /*<<< orphan*/  bt_mesh_adv_send (struct net_buf*,struct bt_mesh_send_cb const*,void*) ; 
 unsigned int bt_mesh_default_ttl_get () ; 
 scalar_t__ bt_mesh_elem_find (int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_fixed_group_match (int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_is_provisioned () ; 
 int bt_mesh_net_encode (struct bt_mesh_net_tx*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bt_mesh_proxy_client_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bt_mesh_proxy_relay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_work_submit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_buf_headroom (struct net_buf*) ; 
 int /*<<< orphan*/  net_buf_ref (struct net_buf*) ; 
 int /*<<< orphan*/  net_buf_slist_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_buf_tailroom (struct net_buf*) ; 
 int /*<<< orphan*/  net_buf_unref (struct net_buf*) ; 
 int /*<<< orphan*/  send_cb_finalize (struct bt_mesh_send_cb const*,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void*) ; 

int bt_mesh_net_send(struct bt_mesh_net_tx *tx, struct net_buf *buf,
                     const struct bt_mesh_send_cb *cb, void *cb_data)
{
    int err;

    BT_DBG("src 0x%04x dst 0x%04x len %u headroom %u tailroom %u",
           tx->src, tx->ctx->addr, buf->len, net_buf_headroom(buf),
           net_buf_tailroom(buf));
    BT_DBG("Payload len %u: %s", buf->len, bt_hex(buf->data, buf->len));
    BT_DBG("Seq 0x%06x", bt_mesh.seq);

    if (tx->ctx->send_ttl == BLE_MESH_TTL_DEFAULT) {
        tx->ctx->send_ttl = bt_mesh_default_ttl_get();
    }

    err = bt_mesh_net_encode(tx, &buf->b, false);
    if (err) {
        goto done;
    }

    /* Deliver to GATT Proxy Clients if necessary. Mesh spec 3.4.5.2:
     * "The output filter of the interface connected to advertising or
     * GATT bearers shall drop all messages with TTL value set to 1."
     */
#if CONFIG_BLE_MESH_NODE
    if (bt_mesh_is_provisioned()) {
        if (IS_ENABLED(CONFIG_BLE_MESH_GATT_PROXY_SERVER) &&
                tx->ctx->send_ttl != 1U) {
            if (bt_mesh_proxy_relay(&buf->b, tx->ctx->addr) &&
                    BLE_MESH_ADDR_IS_UNICAST(tx->ctx->addr)) {
                /* Notify completion if this only went
                * through the Mesh Proxy.
                */
                send_cb_finalize(cb, cb_data);

                err = 0;
                goto done;
            }
        }
    }
#endif

#if CONFIG_BLE_MESH_GATT_PROXY_CLIENT
    if (tx->ctx->send_ttl != 1U) {
        if (bt_mesh_proxy_client_send(&buf->b, tx->ctx->addr)) {
            /* If Proxy Client succeeds to send messages with GATT bearer,
             * we can directly finish here. And if not, which means no
             * connection has been created with Proxy Client, here we will
             * use advertising bearer for the messages.
             */
            send_cb_finalize(cb, cb_data);

            err = 0;
            goto done;
        }
    }
#endif

    /* Deliver to local network interface if necessary */
    if (bt_mesh_fixed_group_match(tx->ctx->addr) ||
            bt_mesh_elem_find(tx->ctx->addr)) {
        if (cb && cb->start) {
            cb->start(0, 0, cb_data);
        }
        net_buf_slist_put(&bt_mesh.local_queue, net_buf_ref(buf));
        if (cb && cb->end) {
            cb->end(0, cb_data);
        }
        k_work_submit(&bt_mesh.local_work);
    } else if (tx->ctx->send_ttl != 1U) {
        /* Deliver to the advertising network interface. Mesh spec
         * 3.4.5.2: "The output filter of the interface connected to
         * advertising or GATT bearers shall drop all messages with
         * TTL value set to 1."
         */
        bt_mesh_adv_send(buf, cb, cb_data);
    }

done:
    net_buf_unref(buf);
    return err;
}