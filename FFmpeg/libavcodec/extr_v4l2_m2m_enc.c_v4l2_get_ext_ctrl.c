#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct v4l2_ext_controls {int count; struct v4l2_ext_control* controls; int /*<<< orphan*/  ctrl_class; TYPE_1__ member_0; } ;
struct v4l2_ext_control {unsigned int id; int value; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ V4L2m2mContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  V4L2_CTRL_CLASS_MPEG ; 
 int /*<<< orphan*/  VIDIOC_G_EXT_CTRLS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_ext_controls*) ; 

__attribute__((used)) static inline int v4l2_get_ext_ctrl(V4L2m2mContext *s, unsigned int id, signed int *value, const char *name)
{
    struct v4l2_ext_controls ctrls = { { 0 } };
    struct v4l2_ext_control ctrl = { 0 };
    int ret;

    /* set ctrls */
    ctrls.ctrl_class = V4L2_CTRL_CLASS_MPEG;
    ctrls.controls = &ctrl;
    ctrls.count = 1;

    /* set ctrl*/
    ctrl.id = id ;

    ret = ioctl(s->fd, VIDIOC_G_EXT_CTRLS, &ctrls);
    if (ret < 0) {
        av_log(s->avctx, AV_LOG_WARNING, "Failed to set %s\n", name);
        return ret;
    }

    *value = ctrl.value;

    return 0;
}