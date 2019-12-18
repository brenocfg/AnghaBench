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
struct sk_buff {int dummy; } ;
struct jme_adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_header_cloned (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
jme_expand_header(struct jme_adapter *jme, struct sk_buff *skb)
{
	if (unlikely(skb_shinfo(skb)->gso_size &&
			skb_header_cloned(skb) &&
			pskb_expand_head(skb, 0, 0, GFP_ATOMIC))) {
		dev_kfree_skb(skb);
		return -1;
	}

	return 0;
}