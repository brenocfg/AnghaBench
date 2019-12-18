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
struct go7007 {int input; TYPE_1__* board_info; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  i2c_adapter_online; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int flags; int num_inputs; int sensor_flags; } ;

/* Variables and functions */
 int EIO ; 
 int GO7007_BOARD_HAS_TUNER ; 
 int GO7007_SENSOR_TV ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  VIDIOC_QUERYSTD ; 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int vidioc_querystd(struct file *file, void *priv, v4l2_std_id *std)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if ((go->board_info->flags & GO7007_BOARD_HAS_TUNER) &&
			go->input == go->board_info->num_inputs - 1) {
		if (!go->i2c_adapter_online)
			return -EIO;
		i2c_clients_command(&go->i2c_adapter, VIDIOC_QUERYSTD, std);
	} else if (go->board_info->sensor_flags & GO7007_SENSOR_TV)
		*std = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM;
	else
		*std = 0;

	return 0;
}