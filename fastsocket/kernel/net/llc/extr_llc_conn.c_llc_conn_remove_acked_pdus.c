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
typedef  scalar_t__ u8 ;
typedef  void* u16 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_sock {int /*<<< orphan*/  pdu_unack_q; } ;
struct llc_pdu_sn {int dummy; } ;

/* Variables and functions */
 int LLC_2_SEQ_NBR_MODULO ; 
 scalar_t__ LLC_I_GET_NS (struct llc_pdu_sn*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 void* skb_queue_len (int /*<<< orphan*/ *) ; 

int llc_conn_remove_acked_pdus(struct sock *sk, u8 nr, u16 *how_many_unacked)
{
	int pdu_pos, i;
	struct sk_buff *skb;
	struct llc_pdu_sn *pdu;
	int nbr_acked = 0;
	struct llc_sock *llc = llc_sk(sk);
	int q_len = skb_queue_len(&llc->pdu_unack_q);

	if (!q_len)
		goto out;
	skb = skb_peek(&llc->pdu_unack_q);
	pdu = llc_pdu_sn_hdr(skb);

	/* finding position of last acked pdu in queue */
	pdu_pos = ((int)LLC_2_SEQ_NBR_MODULO + (int)nr -
			(int)LLC_I_GET_NS(pdu)) % LLC_2_SEQ_NBR_MODULO;

	for (i = 0; i < pdu_pos && i < q_len; i++) {
		skb = skb_dequeue(&llc->pdu_unack_q);
		kfree_skb(skb);
		nbr_acked++;
	}
out:
	*how_many_unacked = skb_queue_len(&llc->pdu_unack_q);
	return nbr_acked;
}