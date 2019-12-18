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
struct tea5764_device {int /*<<< orphan*/  mutex; scalar_t__ users; TYPE_1__* videodev; } ;
struct file {struct tea5764_device* private_data; } ;
struct TYPE_4__ {int minor; } ;
struct TYPE_3__ {int minor; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* video_devdata (struct file*) ; 
 struct tea5764_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int tea5764_open(struct file *file)
{
	/* Currently we support only one device */
	int minor = video_devdata(file)->minor;
	struct tea5764_device *radio = video_drvdata(file);

	if (radio->videodev->minor != minor)
		return -ENODEV;

	mutex_lock(&radio->mutex);
	/* Only exclusive access */
	if (radio->users) {
		mutex_unlock(&radio->mutex);
		return -EBUSY;
	}
	radio->users++;
	mutex_unlock(&radio->mutex);
	file->private_data = radio;
	return 0;
}