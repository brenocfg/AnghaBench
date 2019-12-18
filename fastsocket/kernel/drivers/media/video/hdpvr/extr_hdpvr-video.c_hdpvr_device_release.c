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
struct video_device {int dummy; } ;
struct hdpvr_device {struct hdpvr_device* usbc_buf; int /*<<< orphan*/  i2c_mutex; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdpvr_delete (struct hdpvr_device*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hdpvr_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 struct hdpvr_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void hdpvr_device_release(struct video_device *vdev)
{
	struct hdpvr_device *dev = video_get_drvdata(vdev);

	hdpvr_delete(dev);
	mutex_lock(&dev->io_mutex);
	destroy_workqueue(dev->workqueue);
	mutex_unlock(&dev->io_mutex);

	v4l2_device_unregister(&dev->v4l2_dev);

	/* deregister I2C adapter */
#if defined(CONFIG_I2C) || (CONFIG_I2C_MODULE)
	mutex_lock(&dev->i2c_mutex);
	i2c_del_adapter(&dev->i2c_adapter);
	mutex_unlock(&dev->i2c_mutex);
#endif /* CONFIG_I2C */

	kfree(dev->usbc_buf);
	kfree(dev);
}