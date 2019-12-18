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
typedef  int /*<<< orphan*/  u16_t ;
struct net_buf_simple {int len; } ;
struct bt_mesh_model {int dummy; } ;
struct bt_mesh_elem {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct bt_mesh_model* bt_mesh_model_find (struct bt_mesh_elem*,int /*<<< orphan*/ ) ; 
 struct bt_mesh_model* bt_mesh_model_find_vnd (struct bt_mesh_elem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_buf_simple_pull_le16 (struct net_buf_simple*) ; 

__attribute__((used)) static struct bt_mesh_model *get_model(struct bt_mesh_elem *elem,
                                       struct net_buf_simple *buf, bool *vnd)
{
    if (buf->len < 4) {
        u16_t id;

        id = net_buf_simple_pull_le16(buf);

        BT_DBG("ID 0x%04x addr 0x%04x", id, elem->addr);

        *vnd = false;

        return bt_mesh_model_find(elem, id);
    } else {
        u16_t company, id;

        company = net_buf_simple_pull_le16(buf);
        id = net_buf_simple_pull_le16(buf);

        BT_DBG("Company 0x%04x ID 0x%04x addr 0x%04x", company, id,
               elem->addr);

        *vnd = true;

        return bt_mesh_model_find_vnd(elem, company, id);
    }
}