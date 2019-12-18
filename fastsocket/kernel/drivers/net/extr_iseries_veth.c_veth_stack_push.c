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
struct veth_msg {struct veth_msg* next; } ;
struct veth_lpar_connection {struct veth_msg* msg_stack_head; } ;

/* Variables and functions */

__attribute__((used)) static inline void veth_stack_push(struct veth_lpar_connection *cnx,
				   struct veth_msg *msg)
{
	msg->next = cnx->msg_stack_head;
	cnx->msg_stack_head = msg;
}