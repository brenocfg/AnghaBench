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
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {int mchip_mode; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MCHIP_HIC_MODE_CONT_COMP 129 
#define  MCHIP_HIC_MODE_CONT_OUT 128 
 int /*<<< orphan*/  mchip_cont_compression_start () ; 
 int /*<<< orphan*/  mchip_continuous_start () ; 
 TYPE_1__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *fh, enum v4l2_buf_type i)
{
	mutex_lock(&meye.lock);

	switch (meye.mchip_mode) {
	case MCHIP_HIC_MODE_CONT_OUT:
		mchip_continuous_start();
		break;
	case MCHIP_HIC_MODE_CONT_COMP:
		mchip_cont_compression_start();
		break;
	default:
		mutex_unlock(&meye.lock);
		return -EINVAL;
	}

	mutex_unlock(&meye.lock);

	return 0;
}