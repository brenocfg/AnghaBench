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
struct socket {TYPE_1__* sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {TYPE_2__ sin; } ;
struct sockaddr_rxrpc {int transport_len; TYPE_3__ transport; int /*<<< orphan*/  transport_type; int /*<<< orphan*/  srx_service; int /*<<< orphan*/  srx_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  srx ;
struct TYPE_4__ {int /*<<< orphan*/  sk_allocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CM_PORT ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_RXRPC ; 
 int /*<<< orphan*/  CM_SERVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  afs_async_calls ; 
 int /*<<< orphan*/  afs_incoming_calls ; 
 int /*<<< orphan*/  afs_rx_interceptor ; 
 struct socket* afs_socket ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rxrpc_kernel_intercept_rx_messages (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

int afs_open_socket(void)
{
	struct sockaddr_rxrpc srx;
	struct socket *socket;
	int ret;

	_enter("");

	skb_queue_head_init(&afs_incoming_calls);

	afs_async_calls = create_singlethread_workqueue("kafsd");
	if (!afs_async_calls) {
		_leave(" = -ENOMEM [wq]");
		return -ENOMEM;
	}

	ret = sock_create_kern(AF_RXRPC, SOCK_DGRAM, PF_INET, &socket);
	if (ret < 0) {
		destroy_workqueue(afs_async_calls);
		_leave(" = %d [socket]", ret);
		return ret;
	}

	socket->sk->sk_allocation = GFP_NOFS;

	/* bind the callback manager's address to make this a server socket */
	srx.srx_family			= AF_RXRPC;
	srx.srx_service			= CM_SERVICE;
	srx.transport_type		= SOCK_DGRAM;
	srx.transport_len		= sizeof(srx.transport.sin);
	srx.transport.sin.sin_family	= AF_INET;
	srx.transport.sin.sin_port	= htons(AFS_CM_PORT);
	memset(&srx.transport.sin.sin_addr, 0,
	       sizeof(srx.transport.sin.sin_addr));

	ret = kernel_bind(socket, (struct sockaddr *) &srx, sizeof(srx));
	if (ret < 0) {
		sock_release(socket);
		_leave(" = %d [bind]", ret);
		return ret;
	}

	rxrpc_kernel_intercept_rx_messages(socket, afs_rx_interceptor);

	afs_socket = socket;
	_leave(" = 0");
	return 0;
}