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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_conn_state_ev {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct llc_conn_state_ev* llc_conn_ev (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_process_tmr_ev (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 

__attribute__((used)) static void llc_conn_tmr_common_cb(unsigned long timeout_data, u8 type)
{
	struct sock *sk = (struct sock *)timeout_data;
	struct sk_buff *skb = alloc_skb(0, GFP_ATOMIC);

	bh_lock_sock(sk);
	if (skb) {
		struct llc_conn_state_ev *ev = llc_conn_ev(skb);

		skb_set_owner_r(skb, sk);
		ev->type = type;
		llc_process_tmr_ev(sk, skb);
	}
	bh_unlock_sock(sk);
}