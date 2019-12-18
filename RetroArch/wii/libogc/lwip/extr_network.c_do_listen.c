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
typedef  int /*<<< orphan*/  u32 ;
struct apimsg_msg {TYPE_2__* conn; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tcp; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  mbox; TYPE_1__ pcb; void* err; int /*<<< orphan*/  acceptmbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_MSG_DEBUG ; 
 void* ERR_MEM ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MQBOX_SIZE ; 
 int /*<<< orphan*/  MQ_ERROR_SUCCESSFUL ; 
 int /*<<< orphan*/  MQ_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 
 int /*<<< orphan*/  SYS_MBOX_NULL ; 
 int /*<<< orphan*/  accept_func ; 
 int /*<<< orphan*/  tcp_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_arg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * tcp_listen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_listen(struct apimsg_msg *msg)
{
	u32 dummy = 0;

	if(msg->conn->pcb.tcp!=NULL) {
		switch(msg->conn->type) {
			case NETCONN_RAW:
				LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: listen RAW: cannot listen for RAW.\n"));
				break;
			case NETCONN_UDPLITE:
			case NETCONN_UDPNOCHKSUM:
			case NETCONN_UDP:
				LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: listen UDP: cannot listen for UDP.\n"));
				break;
			case NETCONN_TCP:
				msg->conn->pcb.tcp = tcp_listen(msg->conn->pcb.tcp);
				if(msg->conn->pcb.tcp==NULL)
					msg->conn->err = ERR_MEM;
				else {
					if(msg->conn->acceptmbox==SYS_MBOX_NULL) {
						if(MQ_Init(&msg->conn->acceptmbox,MQBOX_SIZE)!=MQ_ERROR_SUCCESSFUL) {
							msg->conn->err = ERR_MEM;
							break;
						}
					}
					tcp_arg(msg->conn->pcb.tcp,msg->conn);
					tcp_accept(msg->conn->pcb.tcp,accept_func);
				}
				break;
			default:
				break;
		}
	}
	MQ_Send(msg->conn->mbox,&dummy,MQ_MSG_BLOCK);
}