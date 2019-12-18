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
 int /*<<< orphan*/  XPT_DATA ; 
 int /*<<< orphan*/  dprintk (char*,struct sock*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (TYPE_1__*) ; 
 scalar_t__ waitqueue_active (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (scalar_t__) ; 

__attribute__((used)) static void svc_tcp_data_ready(struct sock *sk, int count)
{
	struct svc_sock *svsk = (struct svc_sock *)sk->sk_user_data;

	dprintk("svc: socket %p TCP data ready (svsk %p)\n",
		sk, sk->sk_user_data);
	if (svsk) {
		set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
		svc_xprt_enqueue(&svsk->sk_xprt);
	}
	if (sk->sk_sleep && waitqueue_active(sk->sk_sleep))
		wake_up_interruptible(sk->sk_sleep);
}