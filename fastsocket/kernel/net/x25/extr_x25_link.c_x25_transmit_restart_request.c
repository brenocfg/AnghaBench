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
struct x25_neigh {scalar_t__ extended; } ;
struct sk_buff {int /*<<< orphan*/ * sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  X25_GFI_EXTSEQ ; 
 int /*<<< orphan*/  X25_GFI_STDSEQ ; 
 int X25_MAX_L2_LEN ; 
 int /*<<< orphan*/  X25_RESTART_REQUEST ; 
 int X25_STD_MIN_LEN ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  x25_send_frame (struct sk_buff*,struct x25_neigh*) ; 

__attribute__((used)) static void x25_transmit_restart_request(struct x25_neigh *nb)
{
	unsigned char *dptr;
	int len = X25_MAX_L2_LEN + X25_STD_MIN_LEN + 2;
	struct sk_buff *skb = alloc_skb(len, GFP_ATOMIC);

	if (!skb)
		return;

	skb_reserve(skb, X25_MAX_L2_LEN);

	dptr = skb_put(skb, X25_STD_MIN_LEN + 2);

	*dptr++ = nb->extended ? X25_GFI_EXTSEQ : X25_GFI_STDSEQ;
	*dptr++ = 0x00;
	*dptr++ = X25_RESTART_REQUEST;
	*dptr++ = 0x00;
	*dptr++ = 0;

	skb->sk = NULL;

	x25_send_frame(skb, nb);
}