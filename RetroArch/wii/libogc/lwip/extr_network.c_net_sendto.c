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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct netsocket {int /*<<< orphan*/  conn; } ;
struct ip_addr {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOTSOCK ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 struct netsocket* get_socket (scalar_t__) ; 
 int /*<<< orphan*/  ip_addr_debug_print (int /*<<< orphan*/ ,struct ip_addr*) ; 
 scalar_t__ net_send (scalar_t__,void const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netconn_connect (int /*<<< orphan*/ ,struct ip_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netconn_disconnect (int /*<<< orphan*/ ) ; 
 scalar_t__ netconn_peer (int /*<<< orphan*/ ,struct ip_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

s32 net_sendto(s32 s,const void *data,s32 len,u32 flags,struct sockaddr *to,socklen_t tolen)
{
	struct netsocket *sock;
	struct ip_addr remote_addr, addr;
	u16_t remote_port, port = 0;
	s32 ret,connected;

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_sendto(%d, data=%p, size=%d, flags=0x%x)\n", s, data, len, flags));
	if(data==NULL || len<=0) return -EINVAL;

	sock = get_socket(s);
	if (!sock) return -ENOTSOCK;

	/* get the peer if currently connected */
	connected = (netconn_peer(sock->conn, &addr, &port) == ERR_OK);

	remote_addr.addr = ((struct sockaddr_in *)to)->sin_addr.s_addr;
	remote_port = ((struct sockaddr_in *)to)->sin_port;

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_sendto(%d, data=%p, size=%d, flags=0x%x to=", s, data, len, flags));
	ip_addr_debug_print(SOCKETS_DEBUG, &remote_addr);
	LWIP_DEBUGF(SOCKETS_DEBUG, (" port=%u\n", ntohs(remote_port)));

	netconn_connect(sock->conn, &remote_addr, ntohs(remote_port));

	ret = net_send(s, data, len, flags);

	/* reset the remote address and port number
	of the connection */
	if (connected)
		netconn_connect(sock->conn, &addr, port);
	else
		netconn_disconnect(sock->conn);
	return ret;
}