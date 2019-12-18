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
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int v4l2_cap; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_OSD_SET_STATE ; 
 int EINVAL ; 
 int V4L2_CAP_VIDEO_OUTPUT_OVERLAY ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ivtv_overlay(struct file *file, void *fh, unsigned int on)
{
	struct ivtv_open_id *id = fh;
	struct ivtv *itv = id->itv;

	if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT_OVERLAY))
		return -EINVAL;

	ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, on != 0);

	return 0;
}