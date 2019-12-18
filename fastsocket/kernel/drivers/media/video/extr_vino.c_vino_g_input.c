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
struct vino_channel_settings {int input; } ;
struct file {int dummy; } ;
typedef  unsigned int __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int VINO_INPUT_NONE ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 TYPE_1__* vino_drvdata ; 
 unsigned int vino_find_input_index (struct vino_channel_settings*) ; 

__attribute__((used)) static int vino_g_input(struct file *file, void *__fh,
			     unsigned int *i)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	__u32 index;
	int input;
	unsigned long flags;

	spin_lock_irqsave(&vino_drvdata->input_lock, flags);
	input = vcs->input;
	index = vino_find_input_index(vcs);
	spin_unlock_irqrestore(&vino_drvdata->input_lock, flags);

	dprintk("input = %d\n", input);

	if (input == VINO_INPUT_NONE) {
		return -EINVAL;
	}

	*i = index;

	return 0;
}