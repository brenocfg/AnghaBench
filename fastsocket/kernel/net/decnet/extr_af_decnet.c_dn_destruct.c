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
struct sock {int /*<<< orphan*/  sk_dst_cache; } ;
struct dn_scp {int /*<<< orphan*/  other_receive_queue; int /*<<< orphan*/  other_xmit_queue; int /*<<< orphan*/  data_xmit_queue; } ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dn_destruct(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	skb_queue_purge(&scp->data_xmit_queue);
	skb_queue_purge(&scp->other_xmit_queue);
	skb_queue_purge(&scp->other_receive_queue);

	dst_release(xchg(&sk->sk_dst_cache, NULL));
}