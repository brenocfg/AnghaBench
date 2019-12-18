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
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct netsocket {int /*<<< orphan*/  conn; } ;
struct ip_addr {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int s32 ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int ENOTSOCK ; 
 scalar_t__ ERR_OK ; 
 struct netsocket* get_socket (int) ; 
 scalar_t__ netconn_bind (int /*<<< orphan*/ ,struct ip_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

s32 net_bind(s32 s,struct sockaddr *name,socklen_t namelen)
{
	struct netsocket *sock;
	struct ip_addr loc_addr;
	u16 loc_port;
	err_t err;

	sock = get_socket(s);
	if(!sock) return -ENOTSOCK;

	loc_addr.addr = ((struct sockaddr_in*)name)->sin_addr.s_addr;
	loc_port = ((struct sockaddr_in*)name)->sin_port;

	err = netconn_bind(sock->conn,&loc_addr,ntohs(loc_port));
	if(err!=ERR_OK) return -1;

	return 0;
}