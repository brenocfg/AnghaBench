#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {char* data; int /*<<< orphan*/  truesize; } ;
struct pppoatm_vcc {int flags; int encaps; TYPE_1__* atmvcc; } ;
struct ppp_channel {int dummy; } ;
struct TYPE_8__ {TYPE_1__* vcc; int /*<<< orphan*/  atm_options; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct TYPE_6__ {scalar_t__ (* send ) (TYPE_1__*,struct sk_buff*) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  atm_options; } ;

/* Variables and functions */
 TYPE_5__* ATM_SKB (struct sk_buff*) ; 
 int DROP_PACKET ; 
 int LLC_LEN ; 
 int SC_COMP_PROT ; 
 int /*<<< orphan*/  atm_may_send (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pppoatm_vcc* chan_to_pvcc (struct ppp_channel*) ; 
#define  e_autodetect 130 
#define  e_llc 129 
#define  e_vc 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pppllc ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 TYPE_2__* sk_atm (TYPE_1__*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 scalar_t__ stub1 (TYPE_1__*,struct sk_buff*) ; 

__attribute__((used)) static int pppoatm_send(struct ppp_channel *chan, struct sk_buff *skb)
{
	struct pppoatm_vcc *pvcc = chan_to_pvcc(chan);
	ATM_SKB(skb)->vcc = pvcc->atmvcc;
	pr_debug("pppoatm_send (skb=0x%p, vcc=0x%p)\n", skb, pvcc->atmvcc);
	if (skb->data[0] == '\0' && (pvcc->flags & SC_COMP_PROT))
		(void) skb_pull(skb, 1);
	switch (pvcc->encaps) {		/* LLC encapsulation needed */
	case e_llc:
		if (skb_headroom(skb) < LLC_LEN) {
			struct sk_buff *n;
			n = skb_realloc_headroom(skb, LLC_LEN);
			if (n != NULL &&
			    !atm_may_send(pvcc->atmvcc, n->truesize)) {
				kfree_skb(n);
				goto nospace;
			}
			kfree_skb(skb);
			if ((skb = n) == NULL)
				return DROP_PACKET;
		} else if (!atm_may_send(pvcc->atmvcc, skb->truesize))
			goto nospace;
		memcpy(skb_push(skb, LLC_LEN), pppllc, LLC_LEN);
		break;
	case e_vc:
		if (!atm_may_send(pvcc->atmvcc, skb->truesize))
			goto nospace;
		break;
	case e_autodetect:
		pr_debug("Trying to send without setting encaps!\n");
		kfree_skb(skb);
		return 1;
	}

	atomic_add(skb->truesize, &sk_atm(ATM_SKB(skb)->vcc)->sk_wmem_alloc);
	ATM_SKB(skb)->atm_options = ATM_SKB(skb)->vcc->atm_options;
	pr_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n", skb, ATM_SKB(skb)->vcc,
	    ATM_SKB(skb)->vcc->dev);
	return ATM_SKB(skb)->vcc->send(ATM_SKB(skb)->vcc, skb)
	    ? DROP_PACKET : 1;
    nospace:
	/*
	 * We don't have space to send this SKB now, but we might have
	 * already applied SC_COMP_PROT compression, so may need to undo
	 */
	if ((pvcc->flags & SC_COMP_PROT) && skb_headroom(skb) > 0 &&
	    skb->data[-1] == '\0')
		(void) skb_push(skb, 1);
	return 0;
}