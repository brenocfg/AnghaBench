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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int dummy; } ;
struct dn_skb_cb {int rt_flags; int nsp_flags; } ;
struct dn_scp {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DN_CC ; 
 int DN_RT_F_RTS ; 
 scalar_t__ DN_RUN ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  dn_nsp_conn_ack (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_nsp_conn_conf (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_nsp_conn_init (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_nsp_data (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_nsp_disc_conf (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_nsp_disc_init (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_nsp_linkservice (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_nsp_otherdata (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dn_process_ack (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  dn_returned_conn_init (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int dn_nsp_backlog_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct dn_scp *scp = DN_SK(sk);
	struct dn_skb_cb *cb = DN_SKB_CB(skb);

	if (cb->rt_flags & DN_RT_F_RTS) {
		if (cb->nsp_flags == 0x18 || cb->nsp_flags == 0x68)
			dn_returned_conn_init(sk, skb);
		else
			kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

	/*
	 * Control packet.
	 */
	if ((cb->nsp_flags & 0x0c) == 0x08) {
		switch(cb->nsp_flags & 0x70) {
			case 0x10:
			case 0x60:
				dn_nsp_conn_init(sk, skb);
				break;
			case 0x20:
				dn_nsp_conn_conf(sk, skb);
				break;
			case 0x30:
				dn_nsp_disc_init(sk, skb);
				break;
			case 0x40:
				dn_nsp_disc_conf(sk, skb);
				break;
		}

	} else if (cb->nsp_flags == 0x24) {
		/*
		 * Special for connacks, 'cos they don't have
		 * ack data or ack otherdata info.
		 */
		dn_nsp_conn_ack(sk, skb);
	} else {
		int other = 1;

		/* both data and ack frames can kick a CC socket into RUN */
		if ((scp->state == DN_CC) && !sock_flag(sk, SOCK_DEAD)) {
			scp->state = DN_RUN;
			sk->sk_state = TCP_ESTABLISHED;
			sk->sk_state_change(sk);
		}

		if ((cb->nsp_flags & 0x1c) == 0)
			other = 0;
		if (cb->nsp_flags == 0x04)
			other = 0;

		/*
		 * Read out ack data here, this applies equally
		 * to data, other data, link serivce and both
		 * ack data and ack otherdata.
		 */
		dn_process_ack(sk, skb, other);

		/*
		 * If we've some sort of data here then call a
		 * suitable routine for dealing with it, otherwise
		 * the packet is an ack and can be discarded.
		 */
		if ((cb->nsp_flags & 0x0c) == 0) {

			if (scp->state != DN_RUN)
				goto free_out;

			switch(cb->nsp_flags) {
				case 0x10: /* LS */
					dn_nsp_linkservice(sk, skb);
					break;
				case 0x30: /* OD */
					dn_nsp_otherdata(sk, skb);
					break;
				default:
					dn_nsp_data(sk, skb);
			}

		} else { /* Ack, chuck it out here */
free_out:
			kfree_skb(skb);
		}
	}

	return NET_RX_SUCCESS;
}