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
struct apimsg_msg {TYPE_2__* conn; } ;
struct TYPE_3__ {scalar_t__ tcp; } ;
struct TYPE_4__ {int type; TYPE_1__ pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_MSG_DEBUG ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 

__attribute__((used)) static void do_accept(struct apimsg_msg *msg)
{
	if(msg->conn->pcb.tcp) {
		switch(msg->conn->type) {
			case NETCONN_RAW:
				LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: accept RAW: cannot accept for RAW.\n"));
				break;
			case NETCONN_UDPLITE:
			case NETCONN_UDPNOCHKSUM:
			case NETCONN_UDP:
				LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: accept UDP: cannot accept for UDP.\n"));
				break;
			case NETCONN_TCP:
				break;
		}
	}
}