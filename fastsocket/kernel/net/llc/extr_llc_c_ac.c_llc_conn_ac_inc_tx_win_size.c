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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_sock {scalar_t__ k; } ;

/* Variables and functions */
 scalar_t__ LLC_2_SEQ_NBR_MODULO ; 
 struct llc_sock* llc_sk (struct sock*) ; 

int llc_conn_ac_inc_tx_win_size(struct sock *sk, struct sk_buff *skb)
{
	struct llc_sock *llc = llc_sk(sk);

	llc->k += 1;
	if (llc->k > (u8) ~LLC_2_SEQ_NBR_MODULO)
		llc->k = (u8) ~LLC_2_SEQ_NBR_MODULO;
	return 0;
}