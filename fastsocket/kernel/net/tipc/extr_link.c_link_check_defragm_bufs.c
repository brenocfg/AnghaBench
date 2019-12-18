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
struct sk_buff {struct sk_buff* next; } ;
struct link {struct sk_buff* defragm_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dbg_print_buf_chain (struct sk_buff*) ; 
 int /*<<< orphan*/  dbg_print_link (struct link*,char*) ; 
 int get_timer_cnt (struct sk_buff*) ; 
 int /*<<< orphan*/  incr_timer_cnt (struct sk_buff*) ; 
 int /*<<< orphan*/  link_working_working (struct link*) ; 
 int /*<<< orphan*/  msg_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void link_check_defragm_bufs(struct link *l_ptr)
{
	struct sk_buff *prev = NULL;
	struct sk_buff *next = NULL;
	struct sk_buff *buf = l_ptr->defragm_buf;

	if (!buf)
		return;
	if (!link_working_working(l_ptr))
		return;
	while (buf) {
		u32 cnt = get_timer_cnt(buf);

		next = buf->next;
		if (cnt < 4) {
			incr_timer_cnt(buf);
			prev = buf;
		} else {
			dbg(" Discarding incomplete long buffer\n");
			msg_dbg(buf_msg(buf), "LONG:");
			dbg_print_link(l_ptr, "curr:");
			dbg("Pending long buffers:\n");
			dbg_print_buf_chain(l_ptr->defragm_buf);
			if (prev)
				prev->next = buf->next;
			else
				l_ptr->defragm_buf = buf->next;
			buf_discard(buf);
		}
		buf = next;
	}
}