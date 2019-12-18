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
struct v4l2_frequency {int /*<<< orphan*/  type; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  i2c_adapter_online; TYPE_1__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int GO7007_BOARD_HAS_TUNER ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  VIDIOC_G_FREQUENCY ; 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if (!(go->board_info->flags & GO7007_BOARD_HAS_TUNER))
		return -EINVAL;
	if (!go->i2c_adapter_online)
		return -EIO;

	f->type = V4L2_TUNER_ANALOG_TV;
	i2c_clients_command(&go->i2c_adapter, VIDIOC_G_FREQUENCY, f);
	return 0;
}