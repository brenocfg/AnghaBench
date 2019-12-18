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
struct skb_frag_struct {int page_offset; struct page* page; } ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {struct skb_frag_struct* frags; } ;

/* Variables and functions */
 void* page_address (struct page*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *get_frag_ptr(struct sk_buff *skb)
{
	struct skb_frag_struct *frag =  &skb_shinfo(skb)->frags[0];
	struct page *page = frag->page;
	void *ptr;

	ptr = page_address(page);
	if (unlikely(!ptr))
		return NULL;

	return ptr + frag->page_offset;
}