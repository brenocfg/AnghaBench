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
typedef  int u32_t ;
struct net_buf_simple {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_buf_simple_add_be16 (struct net_buf_simple*,int) ; 
 int /*<<< orphan*/  net_buf_simple_add_le16 (struct net_buf_simple*,int) ; 
 int /*<<< orphan*/  net_buf_simple_add_u8 (struct net_buf_simple*,int) ; 
 int /*<<< orphan*/  net_buf_simple_init (struct net_buf_simple*,int /*<<< orphan*/ ) ; 

void bt_mesh_model_msg_init(struct net_buf_simple *msg, u32_t opcode)
{
    net_buf_simple_init(msg, 0);

    if (opcode < 0x100) {
        /* 1-byte OpCode */
        net_buf_simple_add_u8(msg, opcode);
        return;
    }

    if (opcode < 0x10000) {
        /* 2-byte OpCode */
        net_buf_simple_add_be16(msg, opcode);
        return;
    }

    /* 3-byte OpCode */
    net_buf_simple_add_u8(msg, ((opcode >> 16) & 0xff));
    net_buf_simple_add_le16(msg, opcode & 0xffff);
}