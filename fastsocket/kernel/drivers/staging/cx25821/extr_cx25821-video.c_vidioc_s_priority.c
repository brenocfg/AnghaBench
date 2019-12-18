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
struct file {int dummy; } ;
struct cx25821_fh {int /*<<< orphan*/  prio; struct cx25821_dev* dev; } ;
struct cx25821_dev {int /*<<< orphan*/  prio; } ;
typedef  enum v4l2_priority { ____Placeholder_v4l2_priority } v4l2_priority ;

/* Variables and functions */
 int v4l2_prio_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int vidioc_s_priority(struct file *file, void *f, enum v4l2_priority prio)
{
	struct cx25821_fh *fh = f;
	struct cx25821_dev *dev = ((struct cx25821_fh *)f)->dev;

	return v4l2_prio_change(&dev->prio, &fh->prio, prio);
}