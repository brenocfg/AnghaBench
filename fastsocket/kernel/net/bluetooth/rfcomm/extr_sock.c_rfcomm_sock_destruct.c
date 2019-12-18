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
struct sock {int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct rfcomm_dlc {struct sock* owner; } ;
struct TYPE_2__ {struct rfcomm_dlc* dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_put (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 TYPE_1__* rfcomm_pi (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_sock_destruct(struct sock *sk)
{
	struct rfcomm_dlc *d = rfcomm_pi(sk)->dlc;

	BT_DBG("sk %p dlc %p", sk, d);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_write_queue);

	rfcomm_dlc_lock(d);
	rfcomm_pi(sk)->dlc = NULL;

	/* Detach DLC if it's owned by this socket */
	if (d->owner == sk)
		d->owner = NULL;
	rfcomm_dlc_unlock(d);

	rfcomm_dlc_put(d);
}