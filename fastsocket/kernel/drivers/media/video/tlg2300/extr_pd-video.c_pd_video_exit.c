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
struct video_data {int /*<<< orphan*/  v_dev; } ;
struct vbi_data {int /*<<< orphan*/  v_dev; } ;
struct poseidon {struct vbi_data vbi_data; struct video_data video_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_video_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log () ; 

void pd_video_exit(struct poseidon *pd)
{
	struct video_data *video = &pd->video_data;
	struct vbi_data *vbi = &pd->vbi_data;

	destroy_video_device(&video->v_dev);
	destroy_video_device(&vbi->v_dev);
	log();
}