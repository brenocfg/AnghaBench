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
typedef  int s32 ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int ENOTSOCK ; 
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 struct netsocket* get_socket (int) ; 
 scalar_t__ netconn_listen (int /*<<< orphan*/ ) ; 

s32 net_listen(s32 s,u32 backlog)
{
	struct netsocket *sock;
	err_t err;

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_listen(%d, backlog=%d)\n", s, backlog));
	sock = get_socket(s);
	if(!sock) return -ENOTSOCK;

	err = netconn_listen(sock->conn);
	if(err!=ERR_OK) {
	    LWIP_DEBUGF(SOCKETS_DEBUG, ("net_listen(%d) failed, err=%d\n", s, err));
		return -1;
	}
	return 0;
}