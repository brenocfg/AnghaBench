#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct apimsg_msg {TYPE_2__* conn; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_3__* tcp; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  mbox; int /*<<< orphan*/  err; TYPE_1__ pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_WAIT ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LISTEN ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 
 int /*<<< orphan*/  tcp_close (TYPE_3__*) ; 
 int /*<<< orphan*/  tcp_output (TYPE_3__*) ; 

__attribute__((used)) static void do_close(struct apimsg_msg *msg)
{
	u32 dummy = 0;
	err_t err = ERR_OK;

	if(msg->conn->pcb.tcp) {
		switch(msg->conn->type) {
			case NETCONN_RAW:
			case NETCONN_UDPLITE:
			case NETCONN_UDPNOCHKSUM:
			case NETCONN_UDP:
				break;
			case NETCONN_TCP:
				if(msg->conn->pcb.tcp->state==LISTEN)
					err = tcp_close(msg->conn->pcb.tcp);
				else if(msg->conn->pcb.tcp->state==CLOSE_WAIT)
					err = tcp_output(msg->conn->pcb.tcp);
				msg->conn->err = err;
				break;
			default:
				break;
		}
	}
	MQ_Send(msg->conn->mbox,&dummy,MQ_MSG_BLOCK);
}