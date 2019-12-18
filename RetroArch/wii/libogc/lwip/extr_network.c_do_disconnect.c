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
struct TYPE_3__ {int /*<<< orphan*/  udp; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  mbox; TYPE_1__ pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 
 int /*<<< orphan*/  udp_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_disconnect(struct apimsg_msg *msg)
{
	u32 dummy = 0;

	switch(msg->conn->type) {
		case NETCONN_RAW:
			break;
		case NETCONN_UDPLITE:
		case NETCONN_UDPNOCHKSUM:
		case NETCONN_UDP:
			udp_disconnect(msg->conn->pcb.udp);
			break;
		case NETCONN_TCP:
			break;
	}
	MQ_Send(msg->conn->mbox,&dummy,MQ_MSG_BLOCK);
}