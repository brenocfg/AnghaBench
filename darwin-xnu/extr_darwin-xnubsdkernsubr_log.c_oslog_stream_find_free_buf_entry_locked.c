#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct msgbuf {int msg_bufr; int msg_size; } ;
typedef  TYPE_1__* oslog_stream_buf_entry_t ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ASSERT_OWNED ; 
 int /*<<< orphan*/  LCK_SPIN_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* STAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_AFTER (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_entries ; 
 int /*<<< orphan*/  oslog_s_dropped_msgcount ; 
 int /*<<< orphan*/  oslog_stream_buf_head ; 
 int /*<<< orphan*/  oslog_stream_free_head ; 
 scalar_t__ oslog_stream_link_type_metadata ; 
 int /*<<< orphan*/  oslog_stream_lock ; 
 struct msgbuf* oslog_streambufp ; 

__attribute__((used)) static oslog_stream_buf_entry_t
oslog_stream_find_free_buf_entry_locked(void)
{
	struct msgbuf *mbp;
	oslog_stream_buf_entry_t buf_entry = NULL;

	LCK_SPIN_ASSERT(&oslog_stream_lock, LCK_ASSERT_OWNED);

	mbp = oslog_streambufp;

	buf_entry = STAILQ_FIRST(&oslog_stream_free_head);
	if (buf_entry) {
		STAILQ_REMOVE_HEAD(&oslog_stream_free_head, buf_entries);
	}
	else {
		// If no list elements are available in the free-list,
		// consume the next log line so we can free up its list element
		oslog_stream_buf_entry_t prev_entry = NULL;

		buf_entry = STAILQ_FIRST(&oslog_stream_buf_head);
		while (buf_entry->type == oslog_stream_link_type_metadata) {
			prev_entry = buf_entry;
			buf_entry = STAILQ_NEXT(buf_entry, buf_entries);
		}

		if (prev_entry == NULL) {
			STAILQ_REMOVE_HEAD(&oslog_stream_buf_head, buf_entries);
		}
		else {
			STAILQ_REMOVE_AFTER(&oslog_stream_buf_head, prev_entry, buf_entries);
		}

		mbp->msg_bufr += buf_entry->size;
		oslog_s_dropped_msgcount++;
		if (mbp->msg_bufr >= mbp->msg_size) {
			mbp->msg_bufr = (mbp->msg_bufr % mbp->msg_size);
		}
	}

	return buf_entry;
}