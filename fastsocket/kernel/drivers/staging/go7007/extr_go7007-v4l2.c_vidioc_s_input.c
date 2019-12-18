#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct go7007_file {struct go7007* go; } ;
struct go7007 {unsigned int input; TYPE_2__* board_info; int /*<<< orphan*/  i2c_adapter; scalar_t__ i2c_adapter_online; scalar_t__ streaming; } ;
struct file {int dummy; } ;
struct TYPE_4__ {unsigned int num_inputs; TYPE_1__* inputs; } ;
struct TYPE_3__ {int /*<<< orphan*/  audio_input; int /*<<< orphan*/  video_input; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  VIDIOC_S_AUDIO ; 
 int /*<<< orphan*/  VIDIOC_S_INPUT ; 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int input)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	if (input >= go->board_info->num_inputs)
		return -EINVAL;
	if (go->streaming)
		return -EBUSY;

	go->input = input;
	if (go->i2c_adapter_online) {
		i2c_clients_command(&go->i2c_adapter, VIDIOC_S_INPUT,
			&go->board_info->inputs[input].video_input);
		i2c_clients_command(&go->i2c_adapter, VIDIOC_S_AUDIO,
			&go->board_info->inputs[input].audio_input);
	}

	return 0;
}