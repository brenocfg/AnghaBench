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
typedef  int v4l2_std_id ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {int input; int sensor_framerate; int /*<<< orphan*/  i2c_adapter; scalar_t__ i2c_adapter_online; void* standard; TYPE_1__* board_info; scalar_t__ streaming; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int sensor_flags; int flags; int num_inputs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int GO7007_BOARD_HAS_TUNER ; 
 int GO7007_SENSOR_TV ; 
 void* GO7007_STD_NTSC ; 
 void* GO7007_STD_PAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  VIDIOC_S_STD ; 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_capture_size (struct go7007*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id *std)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if (go->streaming)
		return -EBUSY;

	if (!(go->board_info->sensor_flags & GO7007_SENSOR_TV) &&
			*std != 0)
		return -EINVAL;

	if (*std == 0)
		return -EINVAL;

	if ((go->board_info->flags & GO7007_BOARD_HAS_TUNER) &&
			go->input == go->board_info->num_inputs - 1) {
		if (!go->i2c_adapter_online)
			return -EIO;
		i2c_clients_command(&go->i2c_adapter,
					VIDIOC_S_STD, std);
		if (!*std) /* hack to indicate EINVAL from tuner */
			return -EINVAL;
	}

	if (*std & V4L2_STD_NTSC) {
		go->standard = GO7007_STD_NTSC;
		go->sensor_framerate = 30000;
	} else if (*std & V4L2_STD_PAL) {
		go->standard = GO7007_STD_PAL;
		go->sensor_framerate = 25025;
	} else if (*std & V4L2_STD_SECAM) {
		go->standard = GO7007_STD_PAL;
		go->sensor_framerate = 25025;
	} else
		return -EINVAL;

	if (go->i2c_adapter_online)
		i2c_clients_command(&go->i2c_adapter,
					VIDIOC_S_STD, std);
	set_capture_size(go, NULL, 0);

	return 0;
}