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
struct sk_buff {char* cb; int len; int /*<<< orphan*/  users; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; } ;
struct claw_privbk {TYPE_1__ stats; struct claw_env* p_env; struct chbk* channel; } ;
struct claw_env {scalar_t__ packing; int write_size; } ;
struct chbk {int /*<<< orphan*/  collect_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DO_PACKED ; 
 size_t WRITE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static struct sk_buff *
claw_pack_skb(struct claw_privbk *privptr)
{
	struct sk_buff *new_skb,*held_skb;
	struct chbk *p_ch = &privptr->channel[WRITE];
	struct claw_env  *p_env = privptr->p_env;
	int	pkt_cnt,pk_ind,so_far;

	new_skb = NULL;		/* assume no dice */
	pkt_cnt = 0;
	CLAW_DBF_TEXT(4, trace, "PackSKBe");
	if (!skb_queue_empty(&p_ch->collect_queue)) {
	/* some data */
		held_skb = skb_dequeue(&p_ch->collect_queue);
		if (held_skb)
			dev_kfree_skb_any(held_skb);
		else
			return NULL;
		if (p_env->packing != DO_PACKED)
			return held_skb;
		/* get a new SKB we will pack at least one */
		new_skb = dev_alloc_skb(p_env->write_size);
		if (new_skb == NULL) {
			atomic_inc(&held_skb->users);
			skb_queue_head(&p_ch->collect_queue,held_skb);
			return NULL;
		}
		/* we have packed packet and a place to put it  */
		pk_ind = 1;
		so_far = 0;
		new_skb->cb[1] = 'P'; /* every skb on queue has pack header */
		while ((pk_ind) && (held_skb != NULL)) {
			if (held_skb->len+so_far <= p_env->write_size-8) {
				memcpy(skb_put(new_skb,held_skb->len),
					held_skb->data,held_skb->len);
				privptr->stats.tx_packets++;
				so_far += held_skb->len;
				pkt_cnt++;
				dev_kfree_skb_any(held_skb);
				held_skb = skb_dequeue(&p_ch->collect_queue);
				if (held_skb)
					atomic_dec(&held_skb->users);
			} else {
				pk_ind = 0;
				atomic_inc(&held_skb->users);
				skb_queue_head(&p_ch->collect_queue,held_skb);
			}
		}
	}
	CLAW_DBF_TEXT(4, trace, "PackSKBx");
	return new_skb;
}