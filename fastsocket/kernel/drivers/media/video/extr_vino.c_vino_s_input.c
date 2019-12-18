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
struct vino_channel_settings {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int VINO_INPUT_NONE ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 int vino_int_enum_input (struct vino_channel_settings*,unsigned int) ; 
 int vino_set_input (struct vino_channel_settings*,int) ; 

__attribute__((used)) static int vino_s_input(struct file *file, void *__fh,
			     unsigned int i)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	int input;
	dprintk("requested input = %d\n", i);

	input = vino_int_enum_input(vcs, i);
	if (input == VINO_INPUT_NONE)
		return -EINVAL;

	return vino_set_input(vcs, input);
}