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
typedef  unsigned int u16_t ;
struct net_buf_simple {int dummy; } ;
struct bt_mesh_comp {unsigned int cid; unsigned int pid; unsigned int vid; int elem_count; int /*<<< orphan*/ * elem; } ;

/* Variables and functions */
 unsigned int BLE_MESH_FEAT_FRIEND ; 
 unsigned int BLE_MESH_FEAT_LOW_POWER ; 
 unsigned int BLE_MESH_FEAT_PROXY ; 
 unsigned int BLE_MESH_FEAT_RELAY ; 
 unsigned int CONFIG_BLE_MESH_CRPL ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_FRIEND ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_GATT_PROXY_SERVER ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_LOW_POWER ; 
 int /*<<< orphan*/  CONFIG_BLE_MESH_RELAY ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct bt_mesh_comp* bt_mesh_comp_get () ; 
 int comp_add_elem (struct net_buf_simple*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_buf_simple_add_le16 (struct net_buf_simple*,unsigned int) ; 

__attribute__((used)) static int comp_get_page_0(struct net_buf_simple *buf)
{
    u16_t feat = 0U;
    const struct bt_mesh_comp *comp;
    int i;

    comp = bt_mesh_comp_get();

    if (IS_ENABLED(CONFIG_BLE_MESH_RELAY)) {
        feat |= BLE_MESH_FEAT_RELAY;
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_GATT_PROXY_SERVER)) {
        feat |= BLE_MESH_FEAT_PROXY;
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_FRIEND)) {
        feat |= BLE_MESH_FEAT_FRIEND;
    }

    if (IS_ENABLED(CONFIG_BLE_MESH_LOW_POWER)) {
        feat |= BLE_MESH_FEAT_LOW_POWER;
    }

    net_buf_simple_add_le16(buf, comp->cid);
    net_buf_simple_add_le16(buf, comp->pid);
    net_buf_simple_add_le16(buf, comp->vid);
    net_buf_simple_add_le16(buf, CONFIG_BLE_MESH_CRPL);
    net_buf_simple_add_le16(buf, feat);

    for (i = 0; i < comp->elem_count; i++) {
        int err;

        err = comp_add_elem(buf, &comp->elem[i], i == 0);
        if (err) {
            return err;
        }
    }

    return 0;
}