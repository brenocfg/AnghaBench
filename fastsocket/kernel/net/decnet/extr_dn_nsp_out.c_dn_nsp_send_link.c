#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dn_scp {int /*<<< orphan*/  persist_fxn; int /*<<< orphan*/  persist; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int nsp_flags; } ;

/* Variables and functions */
 scalar_t__ DN_MAX_NSP_DATA_HEADER ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 TYPE_1__* DN_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* dn_alloc_skb (struct sock*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_nsp_persist (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_queue_xmit (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dn_nsp_xmit_timeout ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

void dn_nsp_send_link(struct sock *sk, unsigned char lsflags, char fcval)
{
	struct dn_scp *scp = DN_SK(sk);
	struct sk_buff *skb;
	unsigned char *ptr;
	gfp_t gfp = GFP_ATOMIC;

	if ((skb = dn_alloc_skb(sk, DN_MAX_NSP_DATA_HEADER + 2, gfp)) == NULL)
		return;

	skb_reserve(skb, DN_MAX_NSP_DATA_HEADER);
	ptr = skb_put(skb, 2);
	DN_SKB_CB(skb)->nsp_flags = 0x10;
	*ptr++ = lsflags;
	*ptr = fcval;

	dn_nsp_queue_xmit(sk, skb, gfp, 1);

	scp->persist = dn_nsp_persist(sk);
	scp->persist_fxn = dn_nsp_xmit_timeout;
}