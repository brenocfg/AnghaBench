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
struct sock {int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_sndbuf; } ;
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_may_send (struct atm_vcc*,unsigned int) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,unsigned int,...) ; 
 int /*<<< orphan*/  schedule () ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 scalar_t__ sk_wmem_alloc_get (struct sock*) ; 

__attribute__((used)) static struct sk_buff *alloc_tx(struct atm_vcc *vcc,unsigned int size)
{
	struct sk_buff *skb;
	struct sock *sk = sk_atm(vcc);

	if (sk_wmem_alloc_get(sk) && !atm_may_send(vcc, size)) {
		pr_debug("Sorry: wmem_alloc = %d, size = %d, sndbuf = %d\n",
			sk_wmem_alloc_get(sk), size,
			sk->sk_sndbuf);
		return NULL;
	}
	while (!(skb = alloc_skb(size, GFP_KERNEL)))
		schedule();
	pr_debug("AlTx %d += %d\n", sk_wmem_alloc_get(sk), skb->truesize);
	atomic_add(skb->truesize, &sk->sk_wmem_alloc);
	return skb;
}