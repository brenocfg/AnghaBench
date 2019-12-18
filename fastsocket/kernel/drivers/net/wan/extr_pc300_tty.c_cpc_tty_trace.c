#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; char* data; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; TYPE_1__* dev; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
typedef  TYPE_2__ pc300dev_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_TTY_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_P_CUST ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,char*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void cpc_tty_trace(pc300dev_t *dev, char* buf, int len, char rxtx)
{
	struct sk_buff *skb; 

	if ((skb = dev_alloc_skb(10 + len)) == NULL) { 
		/* out of memory */ 
		CPC_TTY_DBG("%s: tty_trace - out of memory\n", dev->dev->name);
		return; 
	}

	skb_put (skb, 10 + len); 
	skb->dev = dev->dev; 
	skb->protocol = htons(ETH_P_CUST); 
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_HOST; 
	skb->len = 10 + len; 

	skb_copy_to_linear_data(skb, dev->dev->name, 5);
	skb->data[5] = '['; 
	skb->data[6] = rxtx; 
	skb->data[7] = ']'; 
	skb->data[8] = ':'; 
	skb->data[9] = ' '; 
	skb_copy_to_linear_data_offset(skb, 10, buf, len);
	netif_rx(skb); 
}