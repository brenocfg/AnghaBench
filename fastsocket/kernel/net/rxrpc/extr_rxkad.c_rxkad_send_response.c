#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rxrpc_header {int /*<<< orphan*/  serial; scalar_t__ _rsvd; scalar_t__ userStatus; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; scalar_t__ seq; int /*<<< orphan*/  epoch; } ;
struct rxrpc_connection {TYPE_5__* trans; int /*<<< orphan*/  serial; int /*<<< orphan*/  out_clientflag; int /*<<< orphan*/  epoch; } ;
struct rxkad_response {int /*<<< orphan*/  serial; scalar_t__ _rsvd; scalar_t__ userStatus; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; scalar_t__ seq; int /*<<< orphan*/  epoch; } ;
struct rxkad_key {int ticket_len; scalar_t__ ticket; } ;
struct msghdr {int msg_namelen; scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; int /*<<< orphan*/ * msg_name; } ;
struct kvec {int iov_len; struct rxrpc_header* iov_base; } ;
struct TYPE_10__ {TYPE_4__* local; TYPE_3__* peer; } ;
struct TYPE_9__ {int /*<<< orphan*/  socket; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin; } ;
struct TYPE_7__ {TYPE_1__ transport; } ;
struct TYPE_8__ {TYPE_2__ srx; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  RXRPC_PACKET_TYPE_RESPONSE ; 
 int /*<<< orphan*/  _debug (char*,int) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,size_t) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rxkad_send_response(struct rxrpc_connection *conn,
			       struct rxrpc_header *hdr,
			       struct rxkad_response *resp,
			       const struct rxkad_key *s2)
{
	struct msghdr msg;
	struct kvec iov[3];
	size_t len;
	int ret;

	_enter("");

	msg.msg_name	= &conn->trans->peer->srx.transport.sin;
	msg.msg_namelen	= sizeof(conn->trans->peer->srx.transport.sin);
	msg.msg_control	= NULL;
	msg.msg_controllen = 0;
	msg.msg_flags	= 0;

	hdr->epoch	= conn->epoch;
	hdr->seq	= 0;
	hdr->type	= RXRPC_PACKET_TYPE_RESPONSE;
	hdr->flags	= conn->out_clientflag;
	hdr->userStatus	= 0;
	hdr->_rsvd	= 0;

	iov[0].iov_base	= hdr;
	iov[0].iov_len	= sizeof(*hdr);
	iov[1].iov_base	= resp;
	iov[1].iov_len	= sizeof(*resp);
	iov[2].iov_base	= (void *) s2->ticket;
	iov[2].iov_len	= s2->ticket_len;

	len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;

	hdr->serial = htonl(atomic_inc_return(&conn->serial));
	_proto("Tx RESPONSE %%%u", ntohl(hdr->serial));

	ret = kernel_sendmsg(conn->trans->local->socket, &msg, iov, 3, len);
	if (ret < 0) {
		_debug("sendmsg failed: %d", ret);
		return -EAGAIN;
	}

	_leave(" = 0");
	return 0;
}