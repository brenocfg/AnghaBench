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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ext_controls {scalar_t__ ctrl_class; int count; int error_idx; scalar_t__ controls; } ;
struct saa6752hs_state {int /*<<< orphan*/  params; int /*<<< orphan*/  has_ac3; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CTRL_CLASS_MPEG ; 
 int get_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct saa6752hs_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa6752hs_g_ext_ctrls(struct v4l2_subdev *sd, struct v4l2_ext_controls *ctrls)
{
	struct saa6752hs_state *h = to_state(sd);
	int i;

	if (ctrls->ctrl_class != V4L2_CTRL_CLASS_MPEG)
		return -EINVAL;

	for (i = 0; i < ctrls->count; i++) {
		int err = get_ctrl(h->has_ac3, &h->params, ctrls->controls + i);

		if (err) {
			ctrls->error_idx = i;
			return err;
		}
	}
	return 0;
}