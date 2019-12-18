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
struct gspca_dev {int memory; scalar_t__ fr_o; int /*<<< orphan*/  fr_i; int /*<<< orphan*/  streaming; struct file* capt_file; int /*<<< orphan*/  present; } ;
struct file {int dummy; } ;
typedef  enum v4l2_memory { ____Placeholder_v4l2_memory } v4l2_memory ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int frame_ready_nolock(struct gspca_dev *gspca_dev, struct file *file,
				enum v4l2_memory memory)
{
	if (!gspca_dev->present)
		return -ENODEV;
	if (gspca_dev->capt_file != file || gspca_dev->memory != memory ||
			!gspca_dev->streaming)
		return -EINVAL;

	/* check if a frame is ready */
	return gspca_dev->fr_o != atomic_read(&gspca_dev->fr_i);
}