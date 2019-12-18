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
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct atm_vcc {int /*<<< orphan*/  vci; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  sk_wmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void atm_pop_raw(struct atm_vcc *vcc,struct sk_buff *skb)
{
	struct sock *sk = sk_atm(vcc);

	pr_debug("APopR (%d) %d -= %d\n", vcc->vci,
		sk_wmem_alloc_get(sk), skb->truesize);
	atomic_sub(skb->truesize, &sk->sk_wmem_alloc);
	dev_kfree_skb_any(skb);
	sk->sk_write_space(sk);
}