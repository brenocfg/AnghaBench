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
struct v4l2_ctrl {int val; char* string; int type; int step; int minimum; int maximum; char** qmenu; int menu_skip_mask; int /*<<< orphan*/  val64; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
#define  V4L2_CTRL_TYPE_BOOLEAN 134 
#define  V4L2_CTRL_TYPE_BUTTON 133 
#define  V4L2_CTRL_TYPE_CTRL_CLASS 132 
#define  V4L2_CTRL_TYPE_INTEGER 131 
#define  V4L2_CTRL_TYPE_INTEGER64 130 
#define  V4L2_CTRL_TYPE_MENU 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 size_t strlen (char*) ; 

__attribute__((used)) static int validate_new(struct v4l2_ctrl *ctrl)
{
	s32 val = ctrl->val;
	char *s = ctrl->string;
	u32 offset;
	size_t len;

	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_INTEGER:
		/* Round towards the closest legal value */
		val += ctrl->step / 2;
		if (val < ctrl->minimum)
			val = ctrl->minimum;
		if (val > ctrl->maximum)
			val = ctrl->maximum;
		offset = val - ctrl->minimum;
		offset = ctrl->step * (offset / ctrl->step);
		val = ctrl->minimum + offset;
		ctrl->val = val;
		return 0;

	case V4L2_CTRL_TYPE_BOOLEAN:
		ctrl->val = !!ctrl->val;
		return 0;

	case V4L2_CTRL_TYPE_MENU:
		if (val < ctrl->minimum || val > ctrl->maximum)
			return -ERANGE;
		if (ctrl->qmenu[val][0] == '\0' ||
		    (ctrl->menu_skip_mask & (1 << val)))
			return -EINVAL;
		return 0;

	case V4L2_CTRL_TYPE_BUTTON:
	case V4L2_CTRL_TYPE_CTRL_CLASS:
		ctrl->val64 = 0;
		return 0;

	case V4L2_CTRL_TYPE_INTEGER64:
		return 0;

	case V4L2_CTRL_TYPE_STRING:
		len = strlen(s);
		if (len < ctrl->minimum)
			return -ERANGE;
		if ((len - ctrl->minimum) % ctrl->step)
			return -ERANGE;
		return 0;

	default:
		return -EINVAL;
	}
}