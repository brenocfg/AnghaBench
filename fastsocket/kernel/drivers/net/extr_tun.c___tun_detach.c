#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sk; int /*<<< orphan*/ * file; } ;
struct tun_struct {int /*<<< orphan*/  dev; TYPE_2__ socket; int /*<<< orphan*/ * tfile; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __tun_detach(struct tun_struct *tun)
{
	/* Detach from net device */
	netif_tx_lock_bh(tun->dev);
	tun->tfile = NULL;
	tun->socket.file = NULL;
	netif_tx_unlock_bh(tun->dev);

	/* Drop read queue */
	skb_queue_purge(&tun->socket.sk->sk_receive_queue);

	/* Drop the extra count on the net device */
	dev_put(tun->dev);
}