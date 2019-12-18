#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct netsocket {int /*<<< orphan*/  conn; } ;
struct ip_addr {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int s32 ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EISCONN ; 
 int ENOTSOCK ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 struct netsocket* get_socket (int) ; 
 int /*<<< orphan*/  ip_addr_debug_print (int /*<<< orphan*/ ,struct ip_addr*) ; 
 scalar_t__ netconn_connect (int /*<<< orphan*/ ,struct ip_addr*,int /*<<< orphan*/ ) ; 
 scalar_t__ netconn_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

s32 net_connect(s32 s,struct sockaddr *name,socklen_t namelen)
{
	struct netsocket *sock;
	err_t err;

	sock = get_socket(s);
	if(!sock) return -ENOTSOCK;

	if(((struct sockaddr_in*)name)->sin_family==AF_UNSPEC) {
	    LWIP_DEBUGF(SOCKETS_DEBUG, ("net_connect(%d, AF_UNSPEC)\n", s));
		err = netconn_disconnect(sock->conn);
	} else {
		struct ip_addr remote_addr;
		u16 remote_port;

		remote_addr.addr = ((struct sockaddr_in*)name)->sin_addr.s_addr;
		remote_port = ((struct sockaddr_in*)name)->sin_port;

		LWIP_DEBUGF(SOCKETS_DEBUG, ("net_connect(%d, addr=", s));
		ip_addr_debug_print(SOCKETS_DEBUG, &remote_addr);
		LWIP_DEBUGF(SOCKETS_DEBUG, (" port=%u)\n", ntohs(remote_port)));

		err = netconn_connect(sock->conn,&remote_addr,ntohs(remote_port));
	}
	if(err!=ERR_OK) {
	    LWIP_DEBUGF(SOCKETS_DEBUG, ("net_connect(%d) failed, err=%d\n", s, err));
		return -1;
	}

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_connect(%d) succeeded\n", s));
	return -EISCONN;
}