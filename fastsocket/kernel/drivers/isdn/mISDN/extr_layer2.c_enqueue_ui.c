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
struct sk_buff {int dummy; } ;
struct layer2 {scalar_t__ tm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDL_STATUS_UI_IND ; 
 int /*<<< orphan*/  PH_DATA_REQ ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2_newid (struct layer2*) ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ l2down (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static inline void
enqueue_ui(struct layer2 *l2, struct sk_buff *skb)
{
	if (l2->tm)
		l2_tei(l2, MDL_STATUS_UI_IND, 0);
	if (l2down(l2, PH_DATA_REQ, l2_newid(l2), skb))
		dev_kfree_skb(skb);
}