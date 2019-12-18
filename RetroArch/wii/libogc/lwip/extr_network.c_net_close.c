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
struct netsocket {int /*<<< orphan*/ * conn; scalar_t__ lastoffset; int /*<<< orphan*/ * lastdata; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSOCK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_SemPost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_SemWait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 struct netsocket* get_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netbuf_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netconn_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netsocket_sem ; 

s32 net_close(s32 s)
{
	struct netsocket *sock;

	LWIP_DEBUGF(SOCKETS_DEBUG, ("net_close(%d)\n", s));

	LWP_SemWait(netsocket_sem);

	sock = get_socket(s);
	if(!sock) {
		LWP_SemPost(netsocket_sem);
		return -ENOTSOCK;
	}

	netconn_delete(sock->conn);
	if(sock->lastdata) netbuf_delete(sock->lastdata);

	sock->lastdata = NULL;
	sock->lastoffset = 0;
	sock->conn = NULL;

	LWP_SemPost(netsocket_sem);
	return 0;
}