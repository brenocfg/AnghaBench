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
struct video_data {int /*<<< orphan*/ * v_dev; } ;
struct vbi_data {int /*<<< orphan*/ * v_dev; } ;
struct poseidon {struct vbi_data vbi_data; struct video_data video_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VFL_TYPE_VBI ; 
 int /*<<< orphan*/  log (char*,...) ; 
 int /*<<< orphan*/  pd_video_exit (struct poseidon*) ; 
 int /*<<< orphan*/  pd_video_template ; 
 void* vdev_init (struct poseidon*,int /*<<< orphan*/ *) ; 
 int video_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pd_video_init(struct poseidon *pd)
{
	struct video_data *video = &pd->video_data;
	struct vbi_data *vbi	= &pd->vbi_data;
	int ret = -ENOMEM;

	video->v_dev = vdev_init(pd, &pd_video_template);
	if (video->v_dev == NULL)
		goto out;

	ret = video_register_device(video->v_dev, VFL_TYPE_GRABBER, -1);
	if (ret != 0)
		goto out;

	/* VBI uses the same template as video */
	vbi->v_dev = vdev_init(pd, &pd_video_template);
	if (vbi->v_dev == NULL) {
		ret = -ENOMEM;
		goto out;
	}
	ret = video_register_device(vbi->v_dev, VFL_TYPE_VBI, -1);
	if (ret != 0)
		goto out;
	log("register VIDEO/VBI devices");
	return 0;
out:
	log("VIDEO/VBI devices register failed, : %d", ret);
	pd_video_exit(pd);
	return ret;
}