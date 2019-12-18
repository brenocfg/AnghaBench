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
struct sk_buff {int len; int* data; } ;
struct ippp_struct {int pppcfg; } ;

/* Variables and functions */
 int SC_REJ_COMP_AC ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int isdn_ppp_skip_ac(struct ippp_struct *is, struct sk_buff *skb) 
{
	if (skb->len < 1)
		return -1;

	if (skb->data[0] == 0xff) {
		if (skb->len < 2)
			return -1;

		if (skb->data[1] != 0x03)
			return -1;

		// skip address/control (AC) field
		skb_pull(skb, 2);
	} else { 
		if (is->pppcfg & SC_REJ_COMP_AC)
			// if AC compression was not negotiated, but used, discard packet
			return -1;
	}
	return 0;
}