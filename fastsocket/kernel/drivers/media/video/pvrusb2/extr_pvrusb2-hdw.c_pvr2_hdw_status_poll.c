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
struct v4l2_tuner {int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  capability; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  signal; int /*<<< orphan*/  type; } ;
struct pvr2_hdw {scalar_t__ cropcap_stale; struct v4l2_tuner tuner_signal_info; int /*<<< orphan*/  v4l2_dev; scalar_t__ tuner_signal_stale; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_CHIPS ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  memset (struct v4l2_tuner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 

void pvr2_hdw_status_poll(struct pvr2_hdw *hdw)
{
	struct v4l2_tuner *vtp = &hdw->tuner_signal_info;
	memset(vtp, 0, sizeof(*vtp));
	hdw->tuner_signal_stale = 0;
	/* Note: There apparently is no replacement for VIDIOC_CROPCAP
	   using v4l2-subdev - therefore we can't support that AT ALL right
	   now.  (Of course, no sub-drivers seem to implement it either.
	   But now it's a a chicken and egg problem...) */
	v4l2_device_call_all(&hdw->v4l2_dev, 0, tuner, g_tuner,
			     &hdw->tuner_signal_info);
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev status poll"
		   " type=%u strength=%u audio=0x%x cap=0x%x"
		   " low=%u hi=%u",
		   vtp->type,
		   vtp->signal, vtp->rxsubchans, vtp->capability,
		   vtp->rangelow, vtp->rangehigh);

	/* We have to do this to avoid getting into constant polling if
	   there's nobody to answer a poll of cropcap info. */
	hdw->cropcap_stale = 0;
}