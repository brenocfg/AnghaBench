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
struct sk_buff {scalar_t__ truesize; } ;
struct netns_frags {int /*<<< orphan*/  mem; } ;
struct inet_frags {int /*<<< orphan*/  (* skb_free ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static inline void frag_kfree_skb(struct netns_frags *nf, struct inet_frags *f,
		struct sk_buff *skb, int *work)
{
	if (work)
		*work -= skb->truesize;

	atomic_sub(skb->truesize, &nf->mem);
	if (f->skb_free)
		f->skb_free(skb);
	kfree_skb(skb);
}