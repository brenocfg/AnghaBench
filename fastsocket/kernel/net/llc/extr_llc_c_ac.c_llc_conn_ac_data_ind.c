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

/* Variables and functions */
 int /*<<< orphan*/  llc_conn_rtn_pdu (struct sock*,struct sk_buff*) ; 

int llc_conn_ac_data_ind(struct sock *sk, struct sk_buff *skb)
{
	llc_conn_rtn_pdu(sk, skb);
	return 0;
}