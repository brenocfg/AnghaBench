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
struct msgbuf {int msg_bufx; int msg_size; scalar_t__ msg_bufc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ASSERT_OWNED ; 
 int /*<<< orphan*/  LCK_SPIN_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 int /*<<< orphan*/  oslog_stream_lock ; 
 struct msgbuf* oslog_streambufp ; 

__attribute__((used)) static void
oslog_streamwrite_append_bytes(const char *buffer, int buflen)
{
	struct msgbuf *mbp;

	LCK_SPIN_ASSERT(&oslog_stream_lock, LCK_ASSERT_OWNED);

	mbp = oslog_streambufp;
	// Check if we have enough space in the stream buffer to write the data
	if (mbp->msg_bufx + buflen <= mbp->msg_size) {
		memcpy((void *)(mbp->msg_bufc + mbp->msg_bufx), buffer, buflen);

		mbp->msg_bufx += buflen;
		if (mbp->msg_bufx == mbp->msg_size) {
			mbp->msg_bufx = 0;
		}
	} else {
		// Copy part of the data until the end of the stream
		int bytes_left = mbp->msg_size - mbp->msg_bufx;
		memcpy((void *)(mbp->msg_bufc + mbp->msg_bufx), buffer, bytes_left);

		buflen -= bytes_left;
		buffer += bytes_left;

		// Copy the remainder of the data from the beginning of stream
		memcpy((void *)mbp->msg_bufc, buffer, buflen);
		mbp->msg_bufx = buflen;
	}
	return;
}