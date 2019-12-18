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
struct x25_sock {int state; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int X25_STATE_0 ; 
#define  X25_STATE_1 131 
#define  X25_STATE_2 130 
#define  X25_STATE_3 129 
#define  X25_STATE_4 128 
 int x25_decode (struct sock*,struct sk_buff*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  x25_kick (struct sock*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int x25_state1_machine (struct sock*,struct sk_buff*,int) ; 
 int x25_state2_machine (struct sock*,struct sk_buff*,int) ; 
 int x25_state3_machine (struct sock*,struct sk_buff*,int,int,int,int,int,int) ; 
 int x25_state4_machine (struct sock*,struct sk_buff*,int) ; 

int x25_process_rx_frame(struct sock *sk, struct sk_buff *skb)
{
	struct x25_sock *x25 = x25_sk(sk);
	int queued = 0, frametype, ns, nr, q, d, m;

	if (x25->state == X25_STATE_0)
		return 0;

	frametype = x25_decode(sk, skb, &ns, &nr, &q, &d, &m);

	switch (x25->state) {
		case X25_STATE_1:
			queued = x25_state1_machine(sk, skb, frametype);
			break;
		case X25_STATE_2:
			queued = x25_state2_machine(sk, skb, frametype);
			break;
		case X25_STATE_3:
			queued = x25_state3_machine(sk, skb, frametype, ns, nr, q, d, m);
			break;
		case X25_STATE_4:
			queued = x25_state4_machine(sk, skb, frametype);
			break;
	}

	x25_kick(sk);

	return queued;
}