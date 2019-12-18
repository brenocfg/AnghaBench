#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vbi; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct cx18_open_id {int /*<<< orphan*/  prio; struct cx18* cx; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_3__ in; TYPE_2__* sliced_in; } ;
struct cx18 {TYPE_4__ vbi; int /*<<< orphan*/  sd_av; int /*<<< orphan*/  ana_capturing; int /*<<< orphan*/  prio; } ;
struct TYPE_6__ {scalar_t__ service_set; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cx18_g_fmt_vbi_cap (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  cx18_raw_vbi (struct cx18*) ; 
 int /*<<< orphan*/  s_raw_fmt ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbi ; 

__attribute__((used)) static int cx18_s_fmt_vbi_cap(struct file *file, void *fh,
				struct v4l2_format *fmt)
{
	struct cx18_open_id *id = fh;
	struct cx18 *cx = id->cx;
	int ret;

	ret = v4l2_prio_check(&cx->prio, id->prio);
	if (ret)
		return ret;

	/*
	 * Changing the Encoder's Raw VBI parameters won't have any effect
	 * if any analog capture is ongoing
	 */
	if (!cx18_raw_vbi(cx) && atomic_read(&cx->ana_capturing) > 0)
		return -EBUSY;

	/*
	 * Set the digitizer registers for raw active VBI.
	 * Note cx18_av_vbi_wipes out alot of the passed in fmt under valid
	 * calling conditions
	 */
	ret = v4l2_subdev_call(cx->sd_av, vbi, s_raw_fmt, &fmt->fmt.vbi);
	if (ret)
		return ret;

	/* Store our new v4l2 (non-)sliced VBI state */
	cx->vbi.sliced_in->service_set = 0;
	cx->vbi.in.type = V4L2_BUF_TYPE_VBI_CAPTURE;

	return cx18_g_fmt_vbi_cap(file, fh, fmt);
}