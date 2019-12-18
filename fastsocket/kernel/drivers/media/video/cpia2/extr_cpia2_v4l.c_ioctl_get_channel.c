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
struct video_channel {scalar_t__ channel; scalar_t__ norm; int /*<<< orphan*/  type; scalar_t__ flags; scalar_t__ tuners; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VIDEO_TYPE_CAMERA ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ioctl_get_channel(void *arg)
{
	int retval = 0;
	struct video_channel *v;
	v = arg;

	if (v->channel != 0)
		return -EINVAL;

	v->channel = 0;
	strcpy(v->name, "Camera");
	v->tuners = 0;
	v->flags = 0;
	v->type = VIDEO_TYPE_CAMERA;
	v->norm = 0;

	return retval;
}