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
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {scalar_t__ truesize; } ;
struct atm_vcc {TYPE_1__* stats; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  rx_drop; } ;

/* Variables and functions */
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_force_charge (struct atm_vcc*,int) ; 
 int atm_guess_pdu2truesize (int) ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int) ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 

struct sk_buff *atm_alloc_charge(struct atm_vcc *vcc,int pdu_size,
    gfp_t gfp_flags)
{
	struct sock *sk = sk_atm(vcc);
	int guess = atm_guess_pdu2truesize(pdu_size);

	atm_force_charge(vcc,guess);
	if (atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf) {
		struct sk_buff *skb = alloc_skb(pdu_size,gfp_flags);

		if (skb) {
			atomic_add(skb->truesize-guess,
				   &sk->sk_rmem_alloc);
			return skb;
		}
	}
	atm_return(vcc,guess);
	atomic_inc(&vcc->stats->rx_drop);
	return NULL;
}