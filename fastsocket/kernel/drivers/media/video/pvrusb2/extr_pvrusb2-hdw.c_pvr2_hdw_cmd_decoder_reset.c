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
struct pvr2_hdw {scalar_t__ decoder_client_id; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  pvr2_hdw_cx25840_vbi_hack (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pvr2_hdw_cmd_decoder_reset(struct pvr2_hdw *hdw)
{
	pvr2_trace(PVR2_TRACE_INIT,
		   "Requesting decoder reset");
	if (hdw->decoder_client_id) {
		v4l2_device_call_all(&hdw->v4l2_dev, hdw->decoder_client_id,
				     core, reset, 0);
		pvr2_hdw_cx25840_vbi_hack(hdw);
		return 0;
	}
	pvr2_trace(PVR2_TRACE_INIT,
		   "Unable to reset decoder: nothing attached");
	return -ENOTTY;
}