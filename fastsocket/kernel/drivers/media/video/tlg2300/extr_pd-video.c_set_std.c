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
typedef  int v4l2_std_id ;
struct v4l2_pix_format {int height; int sizeimage; int width; } ;
struct running_context {int tvnormid; struct v4l2_pix_format pix; } ;
struct video_data {struct running_context context; } ;
struct vbi_data {int /*<<< orphan*/  vbi_size; } ;
struct poseidon {int /*<<< orphan*/  lock; struct vbi_data vbi_data; struct video_data video_data; } ;
typedef  size_t s32 ;
struct TYPE_2__ {int v4l2_id; size_t tlg_tvnorm; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t POSEIDON_TVNORMS ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L_NTSC_VBI_FRAMESIZE ; 
 int /*<<< orphan*/  V4L_PAL_VBI_FRAMESIZE ; 
 int /*<<< orphan*/  VIDEO_STD_SEL ; 
 int /*<<< orphan*/  log (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* poseidon_tvnorms ; 
 size_t send_set_req (struct poseidon*,int /*<<< orphan*/ ,size_t,size_t*) ; 

__attribute__((used)) static int set_std(struct poseidon *pd, v4l2_std_id *norm)
{
	struct video_data *video = &pd->video_data;
	struct vbi_data *vbi	= &pd->vbi_data;
	struct running_context *context;
	struct v4l2_pix_format *pix;
	s32 i, ret = 0, cmd_status, param;
	int height;

	for (i = 0; i < POSEIDON_TVNORMS; i++) {
		if (*norm & poseidon_tvnorms[i].v4l2_id) {
			param = poseidon_tvnorms[i].tlg_tvnorm;
			log("name : %s", poseidon_tvnorms[i].name);
			goto found;
		}
	}
	return -EINVAL;
found:
	mutex_lock(&pd->lock);
	ret = send_set_req(pd, VIDEO_STD_SEL, param, &cmd_status);
	if (ret || cmd_status)
		goto out;

	/* Set vbi size and check the height of the frame */
	context = &video->context;
	context->tvnormid = poseidon_tvnorms[i].v4l2_id;
	if (context->tvnormid & V4L2_STD_525_60) {
		vbi->vbi_size = V4L_NTSC_VBI_FRAMESIZE;
		height = 480;
	} else {
		vbi->vbi_size = V4L_PAL_VBI_FRAMESIZE;
		height = 576;
	}

	pix = &context->pix;
	if (pix->height != height) {
		pix->height	= height;
		pix->sizeimage 	= pix->width * pix->height * 2;
	}

out:
	mutex_unlock(&pd->lock);
	return ret;
}