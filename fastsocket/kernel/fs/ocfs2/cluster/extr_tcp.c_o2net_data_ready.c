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
struct sock {void (* sk_data_ready ) (struct sock*,int) ;int /*<<< orphan*/  sk_callback_lock; struct o2net_sock_container* sk_user_data; } ;
struct o2net_sock_container {void (* sc_data_ready ) (struct sock*,int) ;int /*<<< orphan*/  sc_rx_work; int /*<<< orphan*/  sc_tv_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_sc_queue_work (struct o2net_sock_container*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclog (struct o2net_sock_container*,char*) ; 

__attribute__((used)) static void o2net_data_ready(struct sock *sk, int bytes)
{
	void (*ready)(struct sock *sk, int bytes);

	read_lock(&sk->sk_callback_lock);
	if (sk->sk_user_data) {
		struct o2net_sock_container *sc = sk->sk_user_data;
		sclog(sc, "data_ready hit\n");
		do_gettimeofday(&sc->sc_tv_data_ready);
		o2net_sc_queue_work(sc, &sc->sc_rx_work);
		ready = sc->sc_data_ready;
	} else {
		ready = sk->sk_data_ready;
	}
	read_unlock(&sk->sk_callback_lock);

	ready(sk, bytes);
}