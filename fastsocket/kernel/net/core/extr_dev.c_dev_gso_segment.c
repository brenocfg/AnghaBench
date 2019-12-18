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
struct sk_buff {int /*<<< orphan*/  destructor; struct sk_buff* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  destructor; } ;

/* Variables and functions */
 TYPE_1__* DEV_GSO_CB (struct sk_buff*) ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_gso_skb_destructor ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int) ; 

__attribute__((used)) static int dev_gso_segment(struct sk_buff *skb, int features)
{
	struct sk_buff *segs;

	segs = skb_gso_segment(skb, features);

	/* Verifying header integrity only. */
	if (!segs)
		return 0;

	if (IS_ERR(segs))
		return PTR_ERR(segs);

	skb->next = segs;
	DEV_GSO_CB(skb)->destructor = skb->destructor;
	skb->destructor = dev_gso_skb_destructor;

	return 0;
}