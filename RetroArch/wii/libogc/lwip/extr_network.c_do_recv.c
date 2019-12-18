#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct apimsg_msg {TYPE_3__* conn; TYPE_2__ msg; } ;
struct TYPE_4__ {scalar_t__ tcp; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  mbox; TYPE_1__ pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NETCONN_TCP ; 
 int /*<<< orphan*/  tcp_recved (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_recv(struct apimsg_msg *msg)
{
	u32 dummy = 0;

	if(msg->conn->pcb.tcp && msg->conn->type==NETCONN_TCP) {
		tcp_recved(msg->conn->pcb.tcp,msg->msg.len);
	}
	MQ_Send(msg->conn->mbox,&dummy,MQ_MSG_BLOCK);
}