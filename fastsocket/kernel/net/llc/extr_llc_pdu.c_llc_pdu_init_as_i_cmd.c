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
struct llc_pdu_sn {int ctrl_1; int ctrl_2; } ;

/* Variables and functions */
 int LLC_I_PF_BIT_MASK ; 
 int LLC_PDU_TYPE_I ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 

void llc_pdu_init_as_i_cmd(struct sk_buff *skb, u8 p_bit, u8 ns, u8 nr)
{
	struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_I;
	pdu->ctrl_2  = 0;
	pdu->ctrl_2 |= (p_bit & LLC_I_PF_BIT_MASK); /* p/f bit */
	pdu->ctrl_1 |= (ns << 1) & 0xFE;   /* set N(S) in bits 2..8 */
	pdu->ctrl_2 |= (nr << 1) & 0xFE;   /* set N(R) in bits 10..16 */
}