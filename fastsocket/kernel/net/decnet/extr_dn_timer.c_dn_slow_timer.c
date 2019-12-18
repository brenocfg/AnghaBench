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
struct TYPE_2__ {scalar_t__ expires; } ;
struct sock {TYPE_1__ sk_timer; } ;
struct dn_scp {scalar_t__ persist; scalar_t__ keepalive; scalar_t__ state; scalar_t__ stamp; int /*<<< orphan*/  (* keepalive_fxn ) (struct sock*) ;scalar_t__ (* persist_fxn ) (struct sock*) ;} ;

/* Variables and functions */
 scalar_t__ DN_RUN ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int HZ ; 
 scalar_t__ SLOW_INTERVAL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static void dn_slow_timer(unsigned long arg)
{
	struct sock *sk = (struct sock *)arg;
	struct dn_scp *scp = DN_SK(sk);

	sock_hold(sk);
	bh_lock_sock(sk);

	if (sock_owned_by_user(sk)) {
		sk->sk_timer.expires = jiffies + HZ / 10;
		add_timer(&sk->sk_timer);
		goto out;
	}

	/*
	 * The persist timer is the standard slow timer used for retransmits
	 * in both connection establishment and disconnection as well as
	 * in the RUN state. The different states are catered for by changing
	 * the function pointer in the socket. Setting the timer to a value
	 * of zero turns it off. We allow the persist_fxn to turn the
	 * timer off in a permant way by returning non-zero, so that
	 * timer based routines may remove sockets. This is why we have a
	 * sock_hold()/sock_put() around the timer to prevent the socket
	 * going away in the middle.
	 */
	if (scp->persist && scp->persist_fxn) {
		if (scp->persist <= SLOW_INTERVAL) {
			scp->persist = 0;

			if (scp->persist_fxn(sk))
				goto out;
		} else {
			scp->persist -= SLOW_INTERVAL;
		}
	}

	/*
	 * Check for keepalive timeout. After the other timer 'cos if
	 * the previous timer caused a retransmit, we don't need to
	 * do this. scp->stamp is the last time that we sent a packet.
	 * The keepalive function sends a link service packet to the
	 * other end. If it remains unacknowledged, the standard
	 * socket timers will eventually shut the socket down. Each
	 * time we do this, scp->stamp will be updated, thus
	 * we won't try and send another until scp->keepalive has passed
	 * since the last successful transmission.
	 */
	if (scp->keepalive && scp->keepalive_fxn && (scp->state == DN_RUN)) {
		if ((jiffies - scp->stamp) >= scp->keepalive)
			scp->keepalive_fxn(sk);
	}

	sk->sk_timer.expires = jiffies + SLOW_INTERVAL;

	add_timer(&sk->sk_timer);
out:
	bh_unlock_sock(sk);
	sock_put(sk);
}