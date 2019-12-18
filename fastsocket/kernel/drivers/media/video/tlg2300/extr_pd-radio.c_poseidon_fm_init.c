#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct TYPE_2__ {struct video_device* fm_dev; } ;
struct poseidon {TYPE_1__ radio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  poseidon_fm_template ; 
 struct video_device* vdev_init (struct poseidon*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 scalar_t__ video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 

int poseidon_fm_init(struct poseidon *p)
{
	struct video_device *fm_dev;

	fm_dev = vdev_init(p, &poseidon_fm_template);
	if (fm_dev == NULL)
		return -1;

	if (video_register_device(fm_dev, VFL_TYPE_RADIO, -1) < 0) {
		video_device_release(fm_dev);
		return -1;
	}
	p->radio_data.fm_dev = fm_dev;
	return 0;
}