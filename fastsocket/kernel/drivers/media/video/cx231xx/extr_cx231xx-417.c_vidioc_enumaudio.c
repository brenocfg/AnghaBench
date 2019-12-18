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
struct v4l2_audio {scalar_t__ index; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_AUDCAP_STEREO ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vidioc_enumaudio(struct file *file, void *fh,
					struct v4l2_audio *a)
{
		struct v4l2_audio *vin = a;

		int ret = -EINVAL;

		if (vin->index > 0)
			return ret;
		strncpy(vin->name, "VideoGrabber Audio", 14);
		vin->capability = V4L2_AUDCAP_STEREO;


return 0;
}