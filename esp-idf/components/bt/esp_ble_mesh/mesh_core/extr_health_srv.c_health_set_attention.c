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
typedef  unsigned int u8_t ;
struct net_buf_simple {int dummy; } ;
struct bt_mesh_msg_ctx {int dummy; } ;
struct bt_mesh_model {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,unsigned int,char*) ; 
 int /*<<< orphan*/  bt_mesh_attention (struct bt_mesh_model*,unsigned int) ; 
 unsigned int net_buf_simple_pull_u8 (struct net_buf_simple*) ; 

__attribute__((used)) static void health_set_attention(struct bt_mesh_model *model,
                                 struct bt_mesh_msg_ctx *ctx,
                                 struct net_buf_simple *buf)
{
    u8_t time;

    time = net_buf_simple_pull_u8(buf);

    BT_DBG("%u second%s", time, (time == 1U) ? "" : "s");

    bt_mesh_attention(model, time);
}