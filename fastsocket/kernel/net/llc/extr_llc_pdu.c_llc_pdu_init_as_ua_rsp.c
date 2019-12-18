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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct llc_pdu_un {int ctrl_1; } ;

/* Variables and functions */
 int LLC_2_PDU_RSP_UA ; 
 int LLC_PDU_TYPE_U ; 
 int LLC_U_PF_BIT_MASK ; 
 struct llc_pdu_un* llc_pdu_un_hdr (struct sk_buff*) ; 

void llc_pdu_init_as_ua_rsp(struct sk_buff *skb, u8 f_bit)
{
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_UA;
	pdu->ctrl_1 |= ((f_bit & 1) << 4) & LLC_U_PF_BIT_MASK;
}