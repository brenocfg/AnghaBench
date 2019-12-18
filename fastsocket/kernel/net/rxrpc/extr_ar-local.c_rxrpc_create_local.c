#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct sock {struct rxrpc_local* sk_user_data; int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_data_ready; } ;
struct TYPE_7__ {int transport_len; int /*<<< orphan*/  transport; int /*<<< orphan*/  transport_type; } ;
struct rxrpc_local {TYPE_2__* socket; int /*<<< orphan*/  link; TYPE_1__ srx; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_8__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_MTU_DISCOVER ; 
 int IP_PMTUDISC_DO ; 
 int /*<<< orphan*/  IP_RECVERR ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,struct rxrpc_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int kernel_bind (TYPE_2__*,struct sockaddr*,int) ; 
 int kernel_setsockopt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_UDP_error_report ; 
 int /*<<< orphan*/  rxrpc_data_ready ; 
 int /*<<< orphan*/  rxrpc_local_lock ; 
 int /*<<< orphan*/  rxrpc_locals ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  sock_release (TYPE_2__*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_create_local(struct rxrpc_local *local)
{
	struct sock *sock;
	int ret, opt;

	_enter("%p{%d}", local, local->srx.transport_type);

	/* create a socket to represent the local endpoint */
	ret = sock_create_kern(PF_INET, local->srx.transport_type, IPPROTO_UDP,
			       &local->socket);
	if (ret < 0) {
		_leave(" = %d [socket]", ret);
		return ret;
	}

	/* if a local address was supplied then bind it */
	if (local->srx.transport_len > sizeof(sa_family_t)) {
		_debug("bind");
		ret = kernel_bind(local->socket,
				  (struct sockaddr *) &local->srx.transport,
				  local->srx.transport_len);
		if (ret < 0) {
			_debug("bind failed");
			goto error;
		}
	}

	/* we want to receive ICMP errors */
	opt = 1;
	ret = kernel_setsockopt(local->socket, SOL_IP, IP_RECVERR,
				(char *) &opt, sizeof(opt));
	if (ret < 0) {
		_debug("setsockopt failed");
		goto error;
	}

	/* we want to set the don't fragment bit */
	opt = IP_PMTUDISC_DO;
	ret = kernel_setsockopt(local->socket, SOL_IP, IP_MTU_DISCOVER,
				(char *) &opt, sizeof(opt));
	if (ret < 0) {
		_debug("setsockopt failed");
		goto error;
	}

	write_lock_bh(&rxrpc_local_lock);
	list_add(&local->link, &rxrpc_locals);
	write_unlock_bh(&rxrpc_local_lock);

	/* set the socket up */
	sock = local->socket->sk;
	sock->sk_user_data	= local;
	sock->sk_data_ready	= rxrpc_data_ready;
	sock->sk_error_report	= rxrpc_UDP_error_report;
	_leave(" = 0");
	return 0;

error:
	kernel_sock_shutdown(local->socket, SHUT_RDWR);
	local->socket->sk->sk_user_data = NULL;
	sock_release(local->socket);
	local->socket = NULL;

	_leave(" = %d", ret);
	return ret;
}