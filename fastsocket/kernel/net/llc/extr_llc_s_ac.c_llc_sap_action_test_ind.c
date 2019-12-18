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
struct sk_buff {int dummy; } ;
struct llc_sap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  llc_sap_rtn_pdu (struct llc_sap*,struct sk_buff*) ; 

int llc_sap_action_test_ind(struct llc_sap *sap, struct sk_buff *skb)
{
	llc_sap_rtn_pdu(sap, skb);
	return 0;
}