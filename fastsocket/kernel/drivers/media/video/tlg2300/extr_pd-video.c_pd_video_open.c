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
struct videobuf_buffer {int dummy; } ;
struct video_device {scalar_t__ vfl_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  users; struct front_face* front; } ;
struct TYPE_3__ {int /*<<< orphan*/  users; int /*<<< orphan*/  context; } ;
struct poseidon {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  interface; int /*<<< orphan*/  kref; TYPE_2__ vbi_data; TYPE_1__ video_data; int /*<<< orphan*/  cur_transfer_mode; } ;
struct front_face {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  active; int /*<<< orphan*/ * curr_frame; struct poseidon* pd; int /*<<< orphan*/  q; void* type; } ;
struct file {struct front_face* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int POSEIDON_STATE_ANALOG ; 
 int POSEIDON_STATE_VBI ; 
 void* V4L2_BUF_TYPE_VBI_CAPTURE ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 scalar_t__ VFL_TYPE_VBI ; 
 int /*<<< orphan*/  debug_mode ; 
 int /*<<< orphan*/  init_video_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct front_face*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct front_face* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pd_video_checkmode (struct poseidon*) ; 
 int /*<<< orphan*/  pd_video_qops ; 
 int /*<<< orphan*/  set_debug_mode (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_transfer_mode ; 
 struct video_device* video_devdata (struct file*) ; 
 struct poseidon* video_get_drvdata (struct video_device*) ; 
 int /*<<< orphan*/  videobuf_queue_vmalloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,struct front_face*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pd_video_open(struct file *file)
{
	struct video_device *vfd = video_devdata(file);
	struct poseidon *pd = video_get_drvdata(vfd);
	struct front_face *front = NULL;
	int ret = -ENOMEM;

	mutex_lock(&pd->lock);
	usb_autopm_get_interface(pd->interface);

	if (vfd->vfl_type == VFL_TYPE_GRABBER
		&& !(pd->state & POSEIDON_STATE_ANALOG)) {
		front = kzalloc(sizeof(struct front_face), GFP_KERNEL);
		if (!front)
			goto out;

		pd->cur_transfer_mode	= usb_transfer_mode;/* bulk or iso */
		init_video_context(&pd->video_data.context);

		ret = pd_video_checkmode(pd);
		if (ret < 0) {
			kfree(front);
			ret = -1;
			goto out;
		}

		pd->state		|= POSEIDON_STATE_ANALOG;
		front->type		= V4L2_BUF_TYPE_VIDEO_CAPTURE;
		pd->video_data.users++;
		set_debug_mode(vfd, debug_mode);

		videobuf_queue_vmalloc_init(&front->q, &pd_video_qops,
				NULL, &front->queue_lock,
				V4L2_BUF_TYPE_VIDEO_CAPTURE,
				V4L2_FIELD_INTERLACED,/* video is interlacd */
				sizeof(struct videobuf_buffer),/*it's enough*/
				front, NULL);
	} else if (vfd->vfl_type == VFL_TYPE_VBI
		&& !(pd->state & POSEIDON_STATE_VBI)) {
		front = kzalloc(sizeof(struct front_face), GFP_KERNEL);
		if (!front)
			goto out;

		pd->state	|= POSEIDON_STATE_VBI;
		front->type	= V4L2_BUF_TYPE_VBI_CAPTURE;
		pd->vbi_data.front = front;
		pd->vbi_data.users++;

		videobuf_queue_vmalloc_init(&front->q, &pd_video_qops,
				NULL, &front->queue_lock,
				V4L2_BUF_TYPE_VBI_CAPTURE,
				V4L2_FIELD_NONE, /* vbi is NONE mode */
				sizeof(struct videobuf_buffer),
				front, NULL);
	} else {
		/* maybe add FM support here */
		log("other ");
		ret = -EINVAL;
		goto out;
	}

	front->pd		= pd;
	front->curr_frame	= NULL;
	INIT_LIST_HEAD(&front->active);
	spin_lock_init(&front->queue_lock);

	file->private_data	= front;
	kref_get(&pd->kref);

	mutex_unlock(&pd->lock);
	return 0;
out:
	usb_autopm_put_interface(pd->interface);
	mutex_unlock(&pd->lock);
	return ret;
}