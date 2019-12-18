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
struct sk_buff {int len; scalar_t__ data; } ;

/* Variables and functions */
 int ath5k_common_padpos (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int ath5k_add_padding(struct sk_buff *skb)
{
	int padpos = ath5k_common_padpos(skb);
	int padsize = padpos & 3;

	if (padsize && skb->len > padpos) {

		if (skb_headroom(skb) < padsize)
			return -1;

		skb_push(skb, padsize);
		memmove(skb->data, skb->data + padsize, padpos);
		return padsize;
	}

	return 0;
}