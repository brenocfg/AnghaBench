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
struct TYPE_2__ {int /*<<< orphan*/  xpt_flags; } ;
struct svc_sock {TYPE_1__ sk_xprt; } ;
struct sock {scalar_t__ sk_sleep; scalar_t__ sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_BUSY ; 
 int /*<<< orphan*/  dprintk (char*,struct svc_sock*,...) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (TYPE_1__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (scalar_t__) ; 

__attribute__((used)) static void svc_write_space(struct sock *sk)
{
	struct svc_sock	*svsk = (struct svc_sock *)(sk->sk_user_data);

	if (svsk) {
		dprintk("svc: socket %p(inet %p), write_space busy=%d\n",
			svsk, sk, test_bit(XPT_BUSY, &svsk->sk_xprt.xpt_flags));
		svc_xprt_enqueue(&svsk->sk_xprt);
	}

	if (sk->sk_sleep && waitqueue_active(sk->sk_sleep)) {
		dprintk("RPC svc_write_space: someone sleeping on %p\n",
		       svsk);
		wake_up_interruptible(sk->sk_sleep);
	}
}