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
struct net_dma_desc_tx {struct net_dma_desc_tx* next; int /*<<< orphan*/ * skb; } ;
struct net_dma_desc_rx {struct net_dma_desc_rx* next; int /*<<< orphan*/ * skb; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CONFIG_BFIN_RX_DESC_NUM ; 
 int CONFIG_BFIN_TX_DESC_NUM ; 
 int /*<<< orphan*/  bfin_mac_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 scalar_t__ rx_desc ; 
 struct net_dma_desc_rx* rx_list_head ; 
 scalar_t__ tx_desc ; 
 struct net_dma_desc_tx* tx_list_head ; 

__attribute__((used)) static void desc_list_free(void)
{
	struct net_dma_desc_rx *r;
	struct net_dma_desc_tx *t;
	int i;
#if !defined(CONFIG_BFIN_MAC_USE_L1)
	dma_addr_t dma_handle = 0;
#endif

	if (tx_desc) {
		t = tx_list_head;
		for (i = 0; i < CONFIG_BFIN_TX_DESC_NUM; i++) {
			if (t) {
				if (t->skb) {
					dev_kfree_skb(t->skb);
					t->skb = NULL;
				}
				t = t->next;
			}
		}
		bfin_mac_free(dma_handle, tx_desc);
	}

	if (rx_desc) {
		r = rx_list_head;
		for (i = 0; i < CONFIG_BFIN_RX_DESC_NUM; i++) {
			if (r) {
				if (r->skb) {
					dev_kfree_skb(r->skb);
					r->skb = NULL;
				}
				r = r->next;
			}
		}
		bfin_mac_free(dma_handle, rx_desc);
	}
}