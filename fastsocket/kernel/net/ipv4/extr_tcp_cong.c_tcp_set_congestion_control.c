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
struct tcp_congestion_ops {int flags; int /*<<< orphan*/  (* init ) (struct sock*) ;int /*<<< orphan*/  owner; } ;
struct sock {scalar_t__ sk_state; } ;
struct inet_connection_sock {struct tcp_congestion_ops* icsk_ca_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EBUSY ; 
 int ENOENT ; 
 int EPERM ; 
 scalar_t__ TCP_CLOSE ; 
 int TCP_CONG_NON_RESTRICTED ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct tcp_congestion_ops* tcp_ca_find (char const*) ; 
 int /*<<< orphan*/  tcp_cleanup_congestion_control (struct sock*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int tcp_set_congestion_control(struct sock *sk, const char *name)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_congestion_ops *ca;
	int err = 0;

	rcu_read_lock();
	ca = tcp_ca_find(name);

	/* no change asking for existing value */
	if (ca == icsk->icsk_ca_ops)
		goto out;

#ifdef CONFIG_MODULES
	/* not found attempt to autoload module */
	if (!ca && capable(CAP_NET_ADMIN)) {
		rcu_read_unlock();
		request_module("tcp_%s", name);
		rcu_read_lock();
		ca = tcp_ca_find(name);
	}
#endif
	if (!ca)
		err = -ENOENT;

	else if (!((ca->flags & TCP_CONG_NON_RESTRICTED) || capable(CAP_NET_ADMIN)))
		err = -EPERM;

	else if (!try_module_get(ca->owner))
		err = -EBUSY;

	else {
		tcp_cleanup_congestion_control(sk);
		icsk->icsk_ca_ops = ca;

		if (sk->sk_state != TCP_CLOSE && icsk->icsk_ca_ops->init)
			icsk->icsk_ca_ops->init(sk);
	}
 out:
	rcu_read_unlock();
	return err;
}