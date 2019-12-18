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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rose_sock {int state; } ;

/* Variables and functions */
 int ROSE_STATE_0 ; 
#define  ROSE_STATE_1 132 
#define  ROSE_STATE_2 131 
#define  ROSE_STATE_3 130 
#define  ROSE_STATE_4 129 
#define  ROSE_STATE_5 128 
 int rose_decode (struct sk_buff*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  rose_kick (struct sock*) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int rose_state1_machine (struct sock*,struct sk_buff*,int) ; 
 int rose_state2_machine (struct sock*,struct sk_buff*,int) ; 
 int rose_state3_machine (struct sock*,struct sk_buff*,int,int,int,int,int,int) ; 
 int rose_state4_machine (struct sock*,struct sk_buff*,int) ; 
 int rose_state5_machine (struct sock*,struct sk_buff*,int) ; 

int rose_process_rx_frame(struct sock *sk, struct sk_buff *skb)
{
	struct rose_sock *rose = rose_sk(sk);
	int queued = 0, frametype, ns, nr, q, d, m;

	if (rose->state == ROSE_STATE_0)
		return 0;

	frametype = rose_decode(skb, &ns, &nr, &q, &d, &m);

	switch (rose->state) {
	case ROSE_STATE_1:
		queued = rose_state1_machine(sk, skb, frametype);
		break;
	case ROSE_STATE_2:
		queued = rose_state2_machine(sk, skb, frametype);
		break;
	case ROSE_STATE_3:
		queued = rose_state3_machine(sk, skb, frametype, ns, nr, q, d, m);
		break;
	case ROSE_STATE_4:
		queued = rose_state4_machine(sk, skb, frametype);
		break;
	case ROSE_STATE_5:
		queued = rose_state5_machine(sk, skb, frametype);
		break;
	}

	rose_kick(sk);

	return queued;
}