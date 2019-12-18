#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_tuner {scalar_t__ index; int /*<<< orphan*/  audmode; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {int board_id; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  i2c_adapter_online; TYPE_1__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  GO7007_BOARDID_PX_TV402U_JP 129 
#define  GO7007_BOARDID_PX_TV402U_NA 128 
 int GO7007_BOARD_HAS_TUNER ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  VIDIOC_S_TUNER ; 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
				struct v4l2_tuner *t)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if (!(go->board_info->flags & GO7007_BOARD_HAS_TUNER))
		return -EINVAL;
	if (t->index != 0)
		return -EINVAL;
	if (!go->i2c_adapter_online)
		return -EIO;

	switch (go->board_id) {
	case GO7007_BOARDID_PX_TV402U_NA:
	case GO7007_BOARDID_PX_TV402U_JP:
		/* No selectable options currently */
		if (t->audmode != V4L2_TUNER_MODE_STEREO)
			return -EINVAL;
		break;
	}

	i2c_clients_command(&go->i2c_adapter, VIDIOC_S_TUNER, t);

	return 0;
}