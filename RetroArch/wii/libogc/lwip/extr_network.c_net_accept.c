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
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct netsocket {int /*<<< orphan*/  rcvevt; int /*<<< orphan*/  conn; } ;
struct netconn {int socket; int /*<<< orphan*/  callback; } ;
struct ip_addr {int /*<<< orphan*/  addr; int /*<<< orphan*/  member_0; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOTSOCK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_SemPost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_SemWait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 int alloc_socket (struct netconn*) ; 
 int /*<<< orphan*/  evt_callback ; 
 struct netsocket* get_socket (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 struct netconn* netconn_accept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netconn_delete (struct netconn*) ; 
 int /*<<< orphan*/  netconn_peer (struct netconn*,struct ip_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netsocket_sem ; 

s32 net_accept(s32 s,struct sockaddr *addr,socklen_t *addrlen)
{
	struct netsocket *sock;
	struct netconn *newconn;
	struct ip_addr naddr = {0};
	u16 port = 0;
	s32 newsock;
	struct sockaddr_in sin;

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_accept(%d)\n", s));

	sock = get_socket(s);
	if(!sock) return -ENOTSOCK;

	newconn = netconn_accept(sock->conn);
	netconn_peer(newconn,&naddr,&port);

	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = naddr.addr;

	if(*addrlen>sizeof(sin))
		*addrlen = sizeof(sin);
	memcpy(addr,&sin,*addrlen);

	newsock = alloc_socket(newconn);
	if(newsock==-1) {
		netconn_delete(newconn);
		return -1;
	}

	newconn->callback = evt_callback;
	sock = get_socket(newsock);

	LWP_SemWait(netsocket_sem);
	sock->rcvevt += -1 - newconn->socket;
	newconn->socket = newsock;
	LWP_SemPost(netsocket_sem);

	return newsock;
}