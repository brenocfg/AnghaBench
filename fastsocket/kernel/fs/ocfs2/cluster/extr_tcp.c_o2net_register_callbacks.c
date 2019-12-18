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
struct sock {scalar_t__ sk_data_ready; scalar_t__ sk_user_data; int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_state_change; } ;
struct o2net_sock_container {scalar_t__ sc_data_ready; int /*<<< orphan*/  sc_send_lock; int /*<<< orphan*/  sc_state_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ o2net_data_ready ; 
 scalar_t__ o2net_listen_data_ready ; 
 int /*<<< orphan*/  o2net_state_change ; 
 int /*<<< orphan*/  sc_get (struct o2net_sock_container*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_register_callbacks(struct sock *sk,
				     struct o2net_sock_container *sc)
{
	write_lock_bh(&sk->sk_callback_lock);

	/* accepted sockets inherit the old listen socket data ready */
	if (sk->sk_data_ready == o2net_listen_data_ready) {
		sk->sk_data_ready = sk->sk_user_data;
		sk->sk_user_data = NULL;
	}

	BUG_ON(sk->sk_user_data != NULL);
	sk->sk_user_data = sc;
	sc_get(sc);

	sc->sc_data_ready = sk->sk_data_ready;
	sc->sc_state_change = sk->sk_state_change;
	sk->sk_data_ready = o2net_data_ready;
	sk->sk_state_change = o2net_state_change;

	mutex_init(&sc->sc_send_lock);

	write_unlock_bh(&sk->sk_callback_lock);
}