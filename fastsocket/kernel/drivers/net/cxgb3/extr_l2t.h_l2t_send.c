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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct l2t_entry {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ L2T_STATE_VALID ; 
 int cxgb3_ofld_send (struct t3cdev*,struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int t3_l2t_send_slow (struct t3cdev*,struct sk_buff*,struct l2t_entry*) ; 

__attribute__((used)) static inline int l2t_send(struct t3cdev *dev, struct sk_buff *skb,
			   struct l2t_entry *e)
{
	if (likely(e->state == L2T_STATE_VALID))
		return cxgb3_ofld_send(dev, skb);
	return t3_l2t_send_slow(dev, skb, e);
}