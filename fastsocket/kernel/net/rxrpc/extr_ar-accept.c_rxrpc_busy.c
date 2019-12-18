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
struct TYPE_2__ {int /*<<< orphan*/  sin; } ;
struct sockaddr_rxrpc {TYPE_1__ transport; } ;
struct rxrpc_local {int /*<<< orphan*/  socket; int /*<<< orphan*/  debug_id; } ;
struct rxrpc_header {int /*<<< orphan*/  serial; scalar_t__ _rsvd; scalar_t__ userStatus; scalar_t__ flags; int /*<<< orphan*/  type; scalar_t__ seq; } ;
struct msghdr {int msg_namelen; scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; int /*<<< orphan*/ * msg_name; } ;
struct kvec {int iov_len; struct rxrpc_header* iov_base; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  RXRPC_PACKET_TYPE_BUSY ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,size_t) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rxrpc_busy(struct rxrpc_local *local, struct sockaddr_rxrpc *srx,
		      struct rxrpc_header *hdr)
{
	struct msghdr msg;
	struct kvec iov[1];
	size_t len;
	int ret;

	_enter("%d,,", local->debug_id);

	msg.msg_name	= &srx->transport.sin;
	msg.msg_namelen	= sizeof(srx->transport.sin);
	msg.msg_control	= NULL;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	hdr->seq	= 0;
	hdr->type	= RXRPC_PACKET_TYPE_BUSY;
	hdr->flags	= 0;
	hdr->userStatus	= 0;
	hdr->_rsvd	= 0;

	iov[0].iov_base	= hdr;
	iov[0].iov_len	= sizeof(*hdr);

	len = iov[0].iov_len;

	hdr->serial = htonl(1);
	_proto("Tx BUSY %%%u", ntohl(hdr->serial));

	ret = kernel_sendmsg(local->socket, &msg, iov, 1, len);
	if (ret < 0) {
		_leave(" = -EAGAIN [sendmsg failed: %d]", ret);
		return -EAGAIN;
	}

	_leave(" = 0");
	return 0;
}