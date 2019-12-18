#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  head; } ;
struct rxrpc_transport {TYPE_4__* peer; TYPE_3__* local; } ;
struct rxrpc_header {int dummy; } ;
struct msghdr {int msg_namelen; scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; int /*<<< orphan*/ * msg_name; } ;
struct kvec {int iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_5__ {int /*<<< orphan*/  sin; } ;
struct TYPE_6__ {TYPE_1__ transport; } ;
struct TYPE_8__ {int maxdata; TYPE_2__ srx; } ;
struct TYPE_7__ {int /*<<< orphan*/  defrag_sem; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IP_MTU_DISCOVER ; 
 int IP_PMTUDISC_DO ; 
 int IP_PMTUDISC_DONT ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*,int,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,int) ; 
 int kernel_setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int rxrpc_send_packet(struct rxrpc_transport *trans, struct sk_buff *skb)
{
	struct kvec iov[1];
	struct msghdr msg;
	int ret, opt;

	_enter(",{%d}", skb->len);

	iov[0].iov_base = skb->head;
	iov[0].iov_len = skb->len;

	msg.msg_name = &trans->peer->srx.transport.sin;
	msg.msg_namelen = sizeof(trans->peer->srx.transport.sin);
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	/* send the packet with the don't fragment bit set if we currently
	 * think it's small enough */
	if (skb->len - sizeof(struct rxrpc_header) < trans->peer->maxdata) {
		down_read(&trans->local->defrag_sem);
		/* send the packet by UDP
		 * - returns -EMSGSIZE if UDP would have to fragment the packet
		 *   to go out of the interface
		 *   - in which case, we'll have processed the ICMP error
		 *     message and update the peer record
		 */
		ret = kernel_sendmsg(trans->local->socket, &msg, iov, 1,
				     iov[0].iov_len);

		up_read(&trans->local->defrag_sem);
		if (ret == -EMSGSIZE)
			goto send_fragmentable;

		_leave(" = %d [%u]", ret, trans->peer->maxdata);
		return ret;
	}

send_fragmentable:
	/* attempt to send this message with fragmentation enabled */
	_debug("send fragment");

	down_write(&trans->local->defrag_sem);
	opt = IP_PMTUDISC_DONT;
	ret = kernel_setsockopt(trans->local->socket, SOL_IP, IP_MTU_DISCOVER,
				(char *) &opt, sizeof(opt));
	if (ret == 0) {
		ret = kernel_sendmsg(trans->local->socket, &msg, iov, 1,
				     iov[0].iov_len);

		opt = IP_PMTUDISC_DO;
		kernel_setsockopt(trans->local->socket, SOL_IP,
				  IP_MTU_DISCOVER, (char *) &opt, sizeof(opt));
	}

	up_write(&trans->local->defrag_sem);
	_leave(" = %d [frag %u]", ret, trans->peer->maxdata);
	return ret;
}