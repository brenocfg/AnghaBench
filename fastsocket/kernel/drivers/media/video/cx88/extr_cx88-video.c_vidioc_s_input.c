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
struct file {int dummy; } ;
struct cx88_core {int /*<<< orphan*/  lock; } ;
struct cx8800_fh {TYPE_1__* dev; } ;
struct TYPE_2__ {struct cx88_core* core; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cx88_newstation (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_video_mux (struct cx88_core*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_s_input (struct file *file, void *priv, unsigned int i)
{
	struct cx88_core  *core = ((struct cx8800_fh *)priv)->dev->core;

	if (i >= 4)
		return -EINVAL;

	mutex_lock(&core->lock);
	cx88_newstation(core);
	cx88_video_mux(core,i);
	mutex_unlock(&core->lock);
	return 0;
}