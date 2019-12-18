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
struct sk_buff {struct sk_buff* next; } ;
struct napi_struct {scalar_t__ gro_count; struct sk_buff* gro_list; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_free_frags (struct napi_struct*) ; 

void netif_napi_del(struct napi_struct *napi)
{
	struct sk_buff *skb, *next;

	list_del_init(&napi->dev_list);
	napi_free_frags(napi);

	for (skb = napi->gro_list; skb; skb = next) {
		next = skb->next;
		skb->next = NULL;
		kfree_skb(skb);
	}

	napi->gro_list = NULL;
	napi->gro_count = 0;
}