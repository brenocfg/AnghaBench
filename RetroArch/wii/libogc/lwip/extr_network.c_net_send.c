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
typedef  int /*<<< orphan*/  u32 ;
struct netsocket {int /*<<< orphan*/  conn; } ;
struct netbuf {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ENOTSOCK ; 
 scalar_t__ ERR_ARG ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETCONN_COPY ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 struct netsocket* get_socket (scalar_t__) ; 
 int /*<<< orphan*/  netbuf_delete (struct netbuf*) ; 
 struct netbuf* netbuf_new () ; 
 int /*<<< orphan*/  netbuf_ref (struct netbuf*,void const*,scalar_t__) ; 
 scalar_t__ netconn_send (int /*<<< orphan*/ ,struct netbuf*) ; 
 int netconn_type (int /*<<< orphan*/ ) ; 
 scalar_t__ netconn_write (int /*<<< orphan*/ ,void const*,scalar_t__,int /*<<< orphan*/ ) ; 

s32 net_send(s32 s,const void *data,s32 len,u32 flags)
{
	struct netsocket *sock;
	struct netbuf *buf;
	err_t err;

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_send(%d, data=%p, size=%d, flags=0x%x)\n", s, data, len, flags));
	if(data==NULL || len<=0) return -EINVAL;

	sock = get_socket(s);
	if(!sock) return -ENOTSOCK;

	switch(netconn_type(sock->conn)) {
		case NETCONN_RAW:
		case NETCONN_UDP:
		case NETCONN_UDPLITE:
		case NETCONN_UDPNOCHKSUM:
			buf = netbuf_new();
			if(!buf) {
				LWIP_DEBUGF(SOCKETS_DEBUG, ("net_send(%d) ENOBUFS\n", s));
				return -ENOBUFS;
			}
			netbuf_ref(buf,data,len);
			err = netconn_send(sock->conn,buf);
			netbuf_delete(buf);
			break;
		case NETCONN_TCP:
			err = netconn_write(sock->conn,data,len,NETCONN_COPY);
			break;
		default:
			err = ERR_ARG;
			break;
	}
	if(err!=ERR_OK) {
		LWIP_DEBUGF(SOCKETS_DEBUG, ("net_send(%d) err=%d\n", s, err));
		return -1;
	}

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_send(%d) ok size=%d\n", s, len));
	return len;
}