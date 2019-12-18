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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {TYPE_2__* tcp; TYPE_1__* udp; } ;
struct netconn {int type; int /*<<< orphan*/  err; TYPE_3__ pcb; } ;
struct ip_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_5__ {int /*<<< orphan*/  remote_port; struct ip_addr remote_ip; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  remote_port; struct ip_addr remote_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_OK ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 
 int UDP_FLAGS_CONNECTED ; 

__attribute__((used)) static err_t netconn_peer(struct netconn *conn,struct ip_addr *addr,u16 *port)
{
	switch(conn->type) {
		case NETCONN_RAW:
			return ERR_CONN;
		case NETCONN_UDPLITE:
		case NETCONN_UDPNOCHKSUM:
		case NETCONN_UDP:
			if(conn->pcb.udp==NULL || ((conn->pcb.udp->flags&UDP_FLAGS_CONNECTED)==0))
				return ERR_CONN;
			*addr = conn->pcb.udp->remote_ip;
			*port = conn->pcb.udp->remote_port;
			break;
		case NETCONN_TCP:
			if(conn->pcb.tcp==NULL)
				return ERR_CONN;
			*addr = conn->pcb.tcp->remote_ip;
			*port = conn->pcb.tcp->remote_port;
			break;
	}
	return (conn->err = ERR_OK);
}