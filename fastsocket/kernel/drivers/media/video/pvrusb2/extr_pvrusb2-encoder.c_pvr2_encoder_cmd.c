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
struct pvr2_hdw {int /*<<< orphan*/  ctl_lock; scalar_t__ state_encoder_runok; scalar_t__ state_encoder_ok; int /*<<< orphan*/  encoder_run_timer; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int IVTV_MBOX_DRIVER_BUSY ; 
 int IVTV_MBOX_DRIVER_DONE ; 
 int IVTV_MBOX_FIRMWARE_DONE ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_BASE ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  PVR2_TRACE_STBITS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int pvr2_encoder_read_words (struct pvr2_hdw*,int /*<<< orphan*/ ,int*,int) ; 
 int pvr2_encoder_write_words (struct pvr2_hdw*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int pvr2_encoder_cmd(void *ctxt,
			    u32 cmd,
			    int arg_cnt_send,
			    int arg_cnt_recv,
			    u32 *argp)
{
	unsigned int poll_count;
	unsigned int try_count = 0;
	int retry_flag;
	int ret = 0;
	unsigned int idx;
	/* These sizes look to be limited by the FX2 firmware implementation */
	u32 wrData[16];
	u32 rdData[16];
	struct pvr2_hdw *hdw = (struct pvr2_hdw *)ctxt;


	/*

	The encoder seems to speak entirely using blocks 32 bit words.
	In ivtv driver terms, this is a mailbox at MBOX_BASE which we
	populate with data and watch what the hardware does with it.
	The first word is a set of flags used to control the
	transaction, the second word is the command to execute, the
	third byte is zero (ivtv driver suggests that this is some
	kind of return value), and the fourth byte is a specified
	timeout (windows driver always uses 0x00060000 except for one
	case when it is zero).  All successive words are the argument
	words for the command.

	First, write out the entire set of words, with the first word
	being zero.

	Next, write out just the first word again, but set it to
	IVTV_MBOX_DRIVER_DONE | IVTV_DRIVER_BUSY this time (which
	probably means "go").

	Next, read back the return count words.  Check the first word,
	which should have IVTV_MBOX_FIRMWARE_DONE set.  If however
	that bit is not set, then the command isn't done so repeat the
	read until it is set.

	Finally, write out just the first word again, but set it to
	0x0 this time (which probably means "idle").

	*/

	if (arg_cnt_send > (ARRAY_SIZE(wrData) - 4)) {
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Failed to write cx23416 command"
			" - too many input arguments"
			" (was given %u limit %lu)",
			arg_cnt_send, (long unsigned) ARRAY_SIZE(wrData) - 4);
		return -EINVAL;
	}

	if (arg_cnt_recv > (ARRAY_SIZE(rdData) - 4)) {
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Failed to write cx23416 command"
			" - too many return arguments"
			" (was given %u limit %lu)",
			arg_cnt_recv, (long unsigned) ARRAY_SIZE(rdData) - 4);
		return -EINVAL;
	}


	LOCK_TAKE(hdw->ctl_lock); do {

		if (!hdw->state_encoder_ok) {
			ret = -EIO;
			break;
		}

		retry_flag = 0;
		try_count++;
		ret = 0;
		wrData[0] = 0;
		wrData[1] = cmd;
		wrData[2] = 0;
		wrData[3] = 0x00060000;
		for (idx = 0; idx < arg_cnt_send; idx++) {
			wrData[idx+4] = argp[idx];
		}
		for (; idx < ARRAY_SIZE(wrData) - 4; idx++) {
			wrData[idx+4] = 0;
		}

		ret = pvr2_encoder_write_words(hdw,MBOX_BASE,wrData,idx);
		if (ret) break;
		wrData[0] = IVTV_MBOX_DRIVER_DONE|IVTV_MBOX_DRIVER_BUSY;
		ret = pvr2_encoder_write_words(hdw,MBOX_BASE,wrData,1);
		if (ret) break;
		poll_count = 0;
		while (1) {
			poll_count++;
			ret = pvr2_encoder_read_words(hdw,MBOX_BASE,rdData,
						      arg_cnt_recv+4);
			if (ret) {
				break;
			}
			if (rdData[0] & IVTV_MBOX_FIRMWARE_DONE) {
				break;
			}
			if (rdData[0] && (poll_count < 1000)) continue;
			if (!rdData[0]) {
				retry_flag = !0;
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"Encoder timed out waiting for us"
					"; arranging to retry");
			} else {
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"***WARNING*** device's encoder"
					" appears to be stuck"
					" (status=0x%08x)",rdData[0]);
			}
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Encoder command: 0x%02x",cmd);
			for (idx = 4; idx < arg_cnt_send; idx++) {
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"Encoder arg%d: 0x%08x",
					idx-3,wrData[idx]);
			}
			ret = -EBUSY;
			break;
		}
		if (retry_flag) {
			if (try_count < 20) continue;
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Too many retries...");
			ret = -EBUSY;
		}
		if (ret) {
			del_timer_sync(&hdw->encoder_run_timer);
			hdw->state_encoder_ok = 0;
			pvr2_trace(PVR2_TRACE_STBITS,
				   "State bit %s <-- %s",
				   "state_encoder_ok",
				   (hdw->state_encoder_ok ? "true" : "false"));
			if (hdw->state_encoder_runok) {
				hdw->state_encoder_runok = 0;
				pvr2_trace(PVR2_TRACE_STBITS,
				   "State bit %s <-- %s",
					   "state_encoder_runok",
					   (hdw->state_encoder_runok ?
					    "true" : "false"));
			}
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Giving up on command."
				"  This is normally recovered via a firmware"
				" reload and re-initialization; concern"
				" is only warranted if this happens repeatedly"
				" and rapidly.");
			break;
		}
		wrData[0] = 0x7;
		for (idx = 0; idx < arg_cnt_recv; idx++) {
			argp[idx] = rdData[idx+4];
		}

		wrData[0] = 0x0;
		ret = pvr2_encoder_write_words(hdw,MBOX_BASE,wrData,1);
		if (ret) break;

	} while(0); LOCK_GIVE(hdw->ctl_lock);

	return ret;
}