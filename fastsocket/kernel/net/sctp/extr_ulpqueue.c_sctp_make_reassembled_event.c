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
struct sk_buff_head {int dummy; } ;
struct sk_buff {struct sk_buff* next; scalar_t__ len; int /*<<< orphan*/  data_len; int /*<<< orphan*/  sk; } ;
struct sctp_ulpevent {int dummy; } ;
struct TYPE_2__ {struct sk_buff* frag_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_REASMUSRMSGS ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_skb_set_owner_r (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sctp_ulpevent *sctp_make_reassembled_event(struct sk_buff_head *queue, struct sk_buff *f_frag, struct sk_buff *l_frag)
{
	struct sk_buff *pos;
	struct sk_buff *new = NULL;
	struct sctp_ulpevent *event;
	struct sk_buff *pnext, *last;
	struct sk_buff *list = skb_shinfo(f_frag)->frag_list;

	/* Store the pointer to the 2nd skb */
	if (f_frag == l_frag)
		pos = NULL;
	else
		pos = f_frag->next;

	/* Get the last skb in the f_frag's frag_list if present. */
	for (last = list; list; last = list, list = list->next);

	/* Add the list of remaining fragments to the first fragments
	 * frag_list.
	 */
	if (last)
		last->next = pos;
	else {
		if (skb_cloned(f_frag)) {
			/* This is a cloned skb, we can't just modify
			 * the frag_list.  We need a new skb to do that.
			 * Instead of calling skb_unshare(), we'll do it
			 * ourselves since we need to delay the free.
			 */
			new = skb_copy(f_frag, GFP_ATOMIC);
			if (!new)
				return NULL;	/* try again later */

			sctp_skb_set_owner_r(new, f_frag->sk);

			skb_shinfo(new)->frag_list = pos;
		} else
			skb_shinfo(f_frag)->frag_list = pos;
	}

	/* Remove the first fragment from the reassembly queue.  */
	__skb_unlink(f_frag, queue);

	/* if we did unshare, then free the old skb and re-assign */
	if (new) {
		kfree_skb(f_frag);
		f_frag = new;
	}

	while (pos) {

		pnext = pos->next;

		/* Update the len and data_len fields of the first fragment. */
		f_frag->len += pos->len;
		f_frag->data_len += pos->len;

		/* Remove the fragment from the reassembly queue.  */
		__skb_unlink(pos, queue);

		/* Break if we have reached the last fragment.  */
		if (pos == l_frag)
			break;
		pos->next = pnext;
		pos = pnext;
	}

	event = sctp_skb2event(f_frag);
	SCTP_INC_STATS(SCTP_MIB_REASMUSRMSGS);

	return event;
}