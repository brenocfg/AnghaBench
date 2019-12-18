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
struct v4l2_queryctrl {int /*<<< orphan*/  name; scalar_t__* reserved; void* default_value; void* step; void* maximum; void* minimum; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  void* s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_fill (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *,void**,void**,void**,void**,int /*<<< orphan*/ *) ; 

int v4l2_ctrl_query_fill(struct v4l2_queryctrl *qctrl, s32 min, s32 max, s32 step, s32 def)
{
	const char *name;

	v4l2_ctrl_fill(qctrl->id, &name, &qctrl->type,
		       &min, &max, &step, &def, &qctrl->flags);

	if (name == NULL)
		return -EINVAL;

	qctrl->minimum = min;
	qctrl->maximum = max;
	qctrl->step = step;
	qctrl->default_value = def;
	qctrl->reserved[0] = qctrl->reserved[1] = 0;
	strlcpy(qctrl->name, name, sizeof(qctrl->name));
	return 0;
}