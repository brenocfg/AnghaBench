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
typedef  int /*<<< orphan*/  u16_t ;
struct net_buf_simple {int dummy; } ;
struct bt_mesh_model {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_MOD_APP_STATUS ; 
 int /*<<< orphan*/  bt_mesh_model_msg_init (struct net_buf_simple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_buf_simple_add (struct net_buf_simple*,int) ; 
 int /*<<< orphan*/  net_buf_simple_add_le16 (struct net_buf_simple*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_buf_simple_add_u8 (struct net_buf_simple*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_mod_app_status(struct net_buf_simple *msg,
                                  struct bt_mesh_model *mod, bool vnd,
                                  u16_t elem_addr, u16_t app_idx,
                                  u8_t status, u8_t *mod_id)
{
    bt_mesh_model_msg_init(msg, OP_MOD_APP_STATUS);

    net_buf_simple_add_u8(msg, status);
    net_buf_simple_add_le16(msg, elem_addr);
    net_buf_simple_add_le16(msg, app_idx);

    if (vnd) {
        memcpy(net_buf_simple_add(msg, 4), mod_id, 4);
    } else {
        memcpy(net_buf_simple_add(msg, 2), mod_id, 2);
    }
}