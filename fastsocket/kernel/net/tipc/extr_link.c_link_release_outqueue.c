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
struct link {scalar_t__ out_queue_size; struct sk_buff* first_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 

__attribute__((used)) static void link_release_outqueue(struct link *l_ptr)
{
	struct sk_buff *buf = l_ptr->first_out;
	struct sk_buff *next;

	while (buf) {
		next = buf->next;
		buf_discard(buf);
		buf = next;
	}
	l_ptr->first_out = NULL;
	l_ptr->out_queue_size = 0;
}