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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct link {scalar_t__ deferred_inqueue_sz; struct sk_buff* oldest_deferred_in; TYPE_1__* newest_deferred_in; int /*<<< orphan*/  next_in_no; } ;
struct TYPE_2__ {struct sk_buff* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 scalar_t__ mod (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_seqno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *link_insert_deferred_queue(struct link *l_ptr,
						  struct sk_buff *buf)
{
	u32 seq_no;

	if (l_ptr->oldest_deferred_in == NULL)
		return buf;

	seq_no = msg_seqno(buf_msg(l_ptr->oldest_deferred_in));
	if (seq_no == mod(l_ptr->next_in_no)) {
		l_ptr->newest_deferred_in->next = buf;
		buf = l_ptr->oldest_deferred_in;
		l_ptr->oldest_deferred_in = NULL;
		l_ptr->deferred_inqueue_sz = 0;
	}
	return buf;
}