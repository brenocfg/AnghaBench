#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct rpc_xprt {scalar_t__ reestablish_timeout; } ;
struct TYPE_4__ {struct rpc_xprt* data; } ;
struct TYPE_5__ {int count; TYPE_1__ arg; } ;
typedef  TYPE_2__ read_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcp_read_sock (struct sock*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct rpc_xprt* xprt_from_sock (struct sock*) ; 
 int /*<<< orphan*/  xs_tcp_data_recv ; 

__attribute__((used)) static void xs_tcp_data_ready(struct sock *sk, int bytes)
{
	struct rpc_xprt *xprt;
	read_descriptor_t rd_desc;
	int read;

	dprintk("RPC:       xs_tcp_data_ready...\n");

	read_lock_bh(&sk->sk_callback_lock);
	if (!(xprt = xprt_from_sock(sk)))
		goto out;
	/* Any data means we had a useful conversation, so
	 * the we don't need to delay the next reconnect
	 */
	if (xprt->reestablish_timeout)
		xprt->reestablish_timeout = 0;

	/* We use rd_desc to pass struct xprt to xs_tcp_data_recv */
	rd_desc.arg.data = xprt;
	do {
		rd_desc.count = 65536;
		read = tcp_read_sock(sk, &rd_desc, xs_tcp_data_recv);
	} while (read > 0);
out:
	read_unlock_bh(&sk->sk_callback_lock);
}