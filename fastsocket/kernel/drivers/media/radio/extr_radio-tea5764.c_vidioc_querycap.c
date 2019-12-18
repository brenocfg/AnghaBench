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
struct TYPE_4__ {TYPE_1__* driver; } ;
struct video_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct tea5764_device {struct video_device* videodev; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIO_VERSION ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_TUNER ; 
 char* dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tea5764_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *v)
{
	struct tea5764_device *radio = video_drvdata(file);
	struct video_device *dev = radio->videodev;

	strlcpy(v->driver, dev->dev.driver->name, sizeof(v->driver));
	strlcpy(v->card, dev->name, sizeof(v->card));
	snprintf(v->bus_info, sizeof(v->bus_info),
		 "I2C:%s", dev_name(&dev->dev));
	v->version = RADIO_VERSION;
	v->capabilities = V4L2_CAP_TUNER | V4L2_CAP_RADIO;
	return 0;
}