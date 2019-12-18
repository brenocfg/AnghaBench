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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;
struct mpoa_client {int /*<<< orphan*/  mpoad_vcc; } ;
struct k_message {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_force_charge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 struct sock* sk_atm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct k_message*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 

int msg_to_mpoad(struct k_message *mesg, struct mpoa_client *mpc)
{
	struct sk_buff *skb;
	struct sock *sk;

	if (mpc == NULL || !mpc->mpoad_vcc) {
		printk("mpoa: msg_to_mpoad: mesg %d to a non-existent mpoad\n", mesg->type);
		return -ENXIO;
	}

	skb = alloc_skb(sizeof(struct k_message), GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;
	skb_put(skb, sizeof(struct k_message));
	skb_copy_to_linear_data(skb, mesg, sizeof(*mesg));
	atm_force_charge(mpc->mpoad_vcc, skb->truesize);

	sk = sk_atm(mpc->mpoad_vcc);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk, skb->len);

	return 0;
}