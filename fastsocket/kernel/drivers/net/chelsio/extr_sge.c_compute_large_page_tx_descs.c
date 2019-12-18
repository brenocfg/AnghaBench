#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int len; unsigned int data_len; } ;
struct TYPE_3__ {unsigned int size; } ;
typedef  TYPE_1__ skb_frag_t ;
struct TYPE_4__ {unsigned int nr_frags; TYPE_1__* frags; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 unsigned int SGE_TX_DESC_MAX_PLEN ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline unsigned int compute_large_page_tx_descs(struct sk_buff *skb)
{
	unsigned int count = 0;

	if (PAGE_SIZE > SGE_TX_DESC_MAX_PLEN) {
		unsigned int nfrags = skb_shinfo(skb)->nr_frags;
		unsigned int i, len = skb->len - skb->data_len;
		while (len > SGE_TX_DESC_MAX_PLEN) {
			count++;
			len -= SGE_TX_DESC_MAX_PLEN;
		}
		for (i = 0; nfrags--; i++) {
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			len = frag->size;
			while (len > SGE_TX_DESC_MAX_PLEN) {
				count++;
				len -= SGE_TX_DESC_MAX_PLEN;
			}
		}
	}
	return count;
}