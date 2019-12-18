#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct apimsg_msg {TYPE_11__* conn; } ;
struct TYPE_16__ {int /*<<< orphan*/  state; } ;
struct TYPE_15__ {int /*<<< orphan*/ * recv_arg; } ;
struct TYPE_14__ {TYPE_3__* tcp; TYPE_2__* udp; int /*<<< orphan*/  raw; } ;
struct TYPE_13__ {int type; scalar_t__ mbox; int /*<<< orphan*/  (* callback ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LISTEN ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_EVTRCVPLUS ; 
 int /*<<< orphan*/  NETCONN_EVTSENDPLUS ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 
 scalar_t__ SYS_MBOX_NULL ; 
 int /*<<< orphan*/  raw_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_abort (TYPE_3__*) ; 
 int /*<<< orphan*/  tcp_accept (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_arg (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_close (TYPE_3__*) ; 
 int /*<<< orphan*/  tcp_err (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_poll (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recv (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_sent (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_remove (TYPE_2__*) ; 

__attribute__((used)) static void do_delconn(struct apimsg_msg *msg)
{
	u32 dummy = 0;

	if(msg->conn->pcb.tcp) {
		switch(msg->conn->type) {
			case NETCONN_RAW:
				raw_remove(msg->conn->pcb.raw);
				break;
			case NETCONN_UDPLITE:
			case NETCONN_UDPNOCHKSUM:
			case NETCONN_UDP:
				msg->conn->pcb.udp->recv_arg = NULL;
				udp_remove(msg->conn->pcb.udp);
				break;
			case NETCONN_TCP:
				if(msg->conn->pcb.tcp->state==LISTEN) {
					tcp_arg(msg->conn->pcb.tcp,NULL);
					tcp_accept(msg->conn->pcb.tcp,NULL);
					tcp_close(msg->conn->pcb.tcp);
				} else {
					tcp_arg(msg->conn->pcb.tcp,NULL);
					tcp_sent(msg->conn->pcb.tcp,NULL);
					tcp_recv(msg->conn->pcb.tcp,NULL);
					tcp_poll(msg->conn->pcb.tcp,NULL,0);
					tcp_err(msg->conn->pcb.tcp,NULL);
					if(tcp_close(msg->conn->pcb.tcp)!=ERR_OK)
						tcp_abort(msg->conn->pcb.tcp);
				}
				break;
			default:
				break;
		}
	}
	if(msg->conn->callback) {
		(*msg->conn->callback)(msg->conn,NETCONN_EVTRCVPLUS,0);
		(*msg->conn->callback)(msg->conn,NETCONN_EVTSENDPLUS,0);
	}
	if(msg->conn->mbox!=SYS_MBOX_NULL)
		MQ_Send(msg->conn->mbox,&dummy,MQ_MSG_BLOCK);
}