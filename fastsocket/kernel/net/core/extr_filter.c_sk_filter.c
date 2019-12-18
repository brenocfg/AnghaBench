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
struct sock {int /*<<< orphan*/  sk_filter; } ;
struct sk_filter {int /*<<< orphan*/  len; int /*<<< orphan*/  insns; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int pskb_trim (struct sk_buff*,unsigned int) ; 
 struct sk_filter* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int security_sock_rcv_skb (struct sock*,struct sk_buff*) ; 
 unsigned int sk_run_filter (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sk_filter(struct sock *sk, struct sk_buff *skb)
{
	int err;
	struct sk_filter *filter;

	err = security_sock_rcv_skb(sk, skb);
	if (err)
		return err;

	rcu_read_lock_bh();
	filter = rcu_dereference(sk->sk_filter);
	if (filter) {
		unsigned int pkt_len = sk_run_filter(skb, filter->insns,
				filter->len);
		err = pkt_len ? pskb_trim(skb, pkt_len) : -EPERM;
	}
	rcu_read_unlock_bh();

	return err;
}