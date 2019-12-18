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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {struct sk_buff* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ less (int,int) ; 
 int msg_seqno (struct tipc_msg*) ; 

u32 tipc_link_defer_pkt(struct sk_buff **head,
			struct sk_buff **tail,
			struct sk_buff *buf)
{
	struct sk_buff *prev = NULL;
	struct sk_buff *crs = *head;
	u32 seq_no = msg_seqno(buf_msg(buf));

	buf->next = NULL;

	/* Empty queue ? */
	if (*head == NULL) {
		*head = *tail = buf;
		return 1;
	}

	/* Last ? */
	if (less(msg_seqno(buf_msg(*tail)), seq_no)) {
		(*tail)->next = buf;
		*tail = buf;
		return 1;
	}

	/* Scan through queue and sort it in */
	do {
		struct tipc_msg *msg = buf_msg(crs);

		if (less(seq_no, msg_seqno(msg))) {
			buf->next = crs;
			if (prev)
				prev->next = buf;
			else
				*head = buf;
			return 1;
		}
		if (seq_no == msg_seqno(msg)) {
			break;
		}
		prev = crs;
		crs = crs->next;
	}
	while (crs);

	/* Message is a duplicate of an existing message */

	buf_discard(buf);
	return 0;
}