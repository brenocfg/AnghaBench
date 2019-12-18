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
struct v4l2_capability {int capabilities; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct radio_si4713_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CAP_MODULATOR ; 
 int V4L2_CAP_RDS_OUTPUT ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct radio_si4713_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radio_si4713_querycap(struct file *file, void *priv,
					struct v4l2_capability *capability)
{
	struct radio_si4713_device *rsdev;

	rsdev = video_get_drvdata(video_devdata(file));

	strlcpy(capability->driver, "radio-si4713", sizeof(capability->driver));
	strlcpy(capability->card, "Silicon Labs Si4713 Modulator",
				sizeof(capability->card));
	capability->capabilities = V4L2_CAP_MODULATOR | V4L2_CAP_RDS_OUTPUT;

	return 0;
}