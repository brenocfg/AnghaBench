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
typedef  int /*<<< orphan*/  oslog_stream_buf_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ASSERT_OWNED ; 
 int /*<<< orphan*/  LCK_SPIN_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_entries ; 
 int /*<<< orphan*/  oslog_stream_buf_head ; 
 int /*<<< orphan*/  oslog_stream_lock ; 

void
oslog_streamwrite_metadata_locked(oslog_stream_buf_entry_t m_entry)
{
	LCK_SPIN_ASSERT(&oslog_stream_lock, LCK_ASSERT_OWNED);
	STAILQ_INSERT_TAIL(&oslog_stream_buf_head, m_entry, buf_entries);

	return;
}