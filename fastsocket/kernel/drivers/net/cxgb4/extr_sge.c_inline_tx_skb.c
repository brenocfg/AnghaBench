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
typedef  scalar_t__ u64 ;
struct sk_buff {int len; int /*<<< orphan*/  data_len; } ;
struct sge_txq {void* desc; scalar_t__ stat; } ;

/* Variables and functions */
 scalar_t__* PTR_ALIGN (void*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff const*,int,void*,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff const*,void*,int) ; 

__attribute__((used)) static void inline_tx_skb(const struct sk_buff *skb, const struct sge_txq *q,
			  void *pos)
{
	u64 *p;
	int left = (void *)q->stat - pos;

	if (likely(skb->len <= left)) {
		if (likely(!skb->data_len))
			skb_copy_from_linear_data(skb, pos, skb->len);
		else
			skb_copy_bits(skb, 0, pos, skb->len);
		pos += skb->len;
	} else {
		skb_copy_bits(skb, 0, pos, left);
		skb_copy_bits(skb, left, q->desc, skb->len - left);
		pos = (void *)q->desc + (skb->len - left);
	}

	/* 0-pad to multiple of 16 */
	p = PTR_ALIGN(pos, 8);
	if ((uintptr_t)p & 8)
		*p = 0;
}