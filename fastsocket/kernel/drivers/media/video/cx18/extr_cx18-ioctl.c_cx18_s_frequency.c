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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;
struct cx18_open_id {int /*<<< orphan*/  prio; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  cx18_mute (struct cx18*) ; 
 int /*<<< orphan*/  cx18_unmute (struct cx18*) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cx18_s_frequency(struct file *file, void *fh, struct v4l2_frequency *vf)
{
	struct cx18_open_id *id = fh;
	struct cx18 *cx = id->cx;
	int ret;

	ret = v4l2_prio_check(&cx->prio, id->prio);
	if (ret)
		return ret;

	if (vf->tuner != 0)
		return -EINVAL;

	cx18_mute(cx);
	CX18_DEBUG_INFO("v4l2 ioctl: set frequency %d\n", vf->frequency);
	cx18_call_all(cx, tuner, s_frequency, vf);
	cx18_unmute(cx);
	return 0;
}