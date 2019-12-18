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
struct pvr2_hdw {unsigned int fw_size; int /*<<< orphan*/  big_lock; scalar_t__ fw_buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVR2_TRACE_FIRMWARE ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,unsigned int,...) ; 

int pvr2_hdw_cpufw_get(struct pvr2_hdw *hdw,unsigned int offs,
		       char *buf,unsigned int cnt)
{
	int ret = -EINVAL;
	LOCK_TAKE(hdw->big_lock); do {
		if (!buf) break;
		if (!cnt) break;

		if (!hdw->fw_buffer) {
			ret = -EIO;
			break;
		}

		if (offs >= hdw->fw_size) {
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Read firmware data offs=%d EOF",
				   offs);
			ret = 0;
			break;
		}

		if (offs + cnt > hdw->fw_size) cnt = hdw->fw_size - offs;

		memcpy(buf,hdw->fw_buffer+offs,cnt);

		pvr2_trace(PVR2_TRACE_FIRMWARE,
			   "Read firmware data offs=%d cnt=%d",
			   offs,cnt);
		ret = cnt;
	} while (0); LOCK_GIVE(hdw->big_lock);

	return ret;
}