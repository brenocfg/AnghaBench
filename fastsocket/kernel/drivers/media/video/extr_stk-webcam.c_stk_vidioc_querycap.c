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
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_VERSION_NUM ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int stk_vidioc_querycap(struct file *filp,
		void *priv, struct v4l2_capability *cap)
{
	strcpy(cap->driver, "stk");
	strcpy(cap->card, "stk");
	cap->version = DRIVER_VERSION_NUM;

	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE
		| V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	return 0;
}