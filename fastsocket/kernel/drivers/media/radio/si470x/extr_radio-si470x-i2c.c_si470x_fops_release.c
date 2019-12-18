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
struct si470x_device {scalar_t__ users; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si470x_stop (struct si470x_device*) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_fops_release(struct file *file)
{
	struct si470x_device *radio = video_drvdata(file);
	int retval = 0;

	/* safety check */
	if (!radio)
		return -ENODEV;

	mutex_lock(&radio->lock);
	radio->users--;
	if (radio->users == 0)
		/* stop radio */
		retval = si470x_stop(radio);

	mutex_unlock(&radio->lock);

	return retval;
}