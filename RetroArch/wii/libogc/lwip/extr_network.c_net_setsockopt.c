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
typedef  void* u8 ;
typedef  int u32 ;
struct netsocket {TYPE_3__* conn; } ;
typedef  int socklen_t ;
typedef  scalar_t__ s32 ;
struct TYPE_5__ {TYPE_1__* tcp; } ;
struct TYPE_6__ {TYPE_2__ pcb; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int so_options; int keepalive; int /*<<< orphan*/  flags; void* tos; void* ttl; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOPROTOOPT ; 
 scalar_t__ ENOTSOCK ; 
#define  IPPROTO_IP 138 
#define  IPPROTO_TCP 137 
#define  IP_TOS 136 
#define  IP_TTL 135 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETCONN_TCP ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
#define  SOL_SOCKET 134 
#define  SO_BROADCAST 133 
#define  SO_KEEPALIVE 132 
#define  SO_REUSEADDR 131 
#define  SO_REUSEPORT 130 
#define  TCP_KEEPALIVE 129 
#define  TCP_NODELAY 128 
 int /*<<< orphan*/  TF_NODELAY ; 
 struct netsocket* get_socket (scalar_t__) ; 

s32 net_setsockopt(s32 s,u32 level,u32 optname,const void *optval,socklen_t optlen)
{
	s32 err = 0;
	struct netsocket *sock;

	sock = get_socket(s);
	if(sock==NULL) return -ENOTSOCK;
	if(optval==NULL) return -EINVAL;

	switch(level) {
		case SOL_SOCKET:
		{
			switch(optname) {
				case SO_BROADCAST:
				case SO_KEEPALIVE:
				case SO_REUSEADDR:
				case SO_REUSEPORT:
					if(optlen<sizeof(u32)) err = EINVAL;
					break;
				default:
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, SOL_SOCKET, UNIMPL: optname=0x%x, ..)\n", s, optname));
					err = ENOPROTOOPT;
			}
		}
		break;

		case IPPROTO_IP:
		{
			switch(optname) {
				case IP_TTL:
				case IP_TOS:
					if(optlen<sizeof(u32)) err = EINVAL;
					break;
				default:
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, IPPROTO_IP, UNIMPL: optname=0x%x, ..)\n", s, optname));
					err = ENOPROTOOPT;
			}
		}
		break;

		case  IPPROTO_TCP:
		{
			if(optlen<sizeof(u32)) {
				err = EINVAL;
				break;
			}
			if(sock->conn->type!=NETCONN_TCP) return 0;

			switch(optname) {
				case TCP_NODELAY:
				case TCP_KEEPALIVE:
					break;
				default:
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, IPPROTO_TCP, UNIMPL: optname=0x%x, ..)\n", s, optname));
					err = ENOPROTOOPT;
			}
		}
		break;

		default:
			LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, level=0x%x, UNIMPL: optname=0x%x, ..)\n", s, level, optname));
			err = ENOPROTOOPT;
	}
	if(err!=0) return -1;

	switch(level) {
		case SOL_SOCKET:
		{
			switch(optname) {
				case SO_BROADCAST:
				case SO_KEEPALIVE:
				case SO_REUSEADDR:
				case SO_REUSEPORT:
					if(*(u32*)optval)
						sock->conn->pcb.tcp->so_options |= optname;
					else
						sock->conn->pcb.tcp->so_options &= ~optname;
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, SOL_SOCKET, optname=0x%x, ..) -> %s\n", s, optname, (*(u32*)optval?"on":"off")));
					break;
			}
		}
		break;

		case IPPROTO_IP:
		{
			switch(optname) {
				case IP_TTL:
					sock->conn->pcb.tcp->ttl = (u8)(*(u32*)optval);
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, IPPROTO_IP, IP_TTL, ..) -> %u\n", s, sock->conn->pcb.tcp->ttl));
					break;
				case IP_TOS:
					sock->conn->pcb.tcp->tos = (u8)(*(u32*)optval);
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, IPPROTO_IP, IP_TOS, ..)-> %u\n", s, sock->conn->pcb.tcp->tos));
					break;
			}
		}
		break;

		case  IPPROTO_TCP:
		{
			switch(optname) {
				case TCP_NODELAY:
					if(*(u32*)optval)
						sock->conn->pcb.tcp->flags |= TF_NODELAY;
					else
						sock->conn->pcb.tcp->flags &= ~TF_NODELAY;
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, IPPROTO_TCP, TCP_NODELAY) -> %s\n", s, (*(u32*)optval)?"on":"off") );
					break;
				case TCP_KEEPALIVE:
					sock->conn->pcb.tcp->keepalive = (u32)(*(u32*)optval);
					LWIP_DEBUGF(SOCKETS_DEBUG, ("net_setsockopt(%d, IPPROTO_TCP, TCP_KEEPALIVE) -> %u\n", s, sock->conn->pcb.tcp->keepalive));
					break;
			}
		}
	}
	return err?-1:0;
}