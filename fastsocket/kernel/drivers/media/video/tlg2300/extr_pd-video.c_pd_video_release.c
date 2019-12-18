#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  users; int /*<<< orphan*/ * front; } ;
struct TYPE_5__ {int /*<<< orphan*/  users; } ;
struct poseidon {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; int /*<<< orphan*/  interface; TYPE_1__ vbi_data; int /*<<< orphan*/  state; TYPE_2__ video_data; int /*<<< orphan*/ * file_for_stream; } ;
struct front_face {scalar_t__ type; int /*<<< orphan*/  q; struct poseidon* pd; } ;
struct file {struct front_face* private_data; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PLAY_SERVICE ; 
 int /*<<< orphan*/  POSEIDON_STATE_ANALOG ; 
 int /*<<< orphan*/  POSEIDON_STATE_VBI ; 
 int /*<<< orphan*/  TLG_TUNE_PLAY_SVC_STOP ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  free_all_urb (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct front_face*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logs (struct front_face*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poseidon_delete ; 
 int /*<<< orphan*/  send_set_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_transfer_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pd_video_release(struct file *file)
{
	struct front_face *front = file->private_data;
	struct poseidon *pd = front->pd;
	s32 cmd_status = 0;

	logs(front);
	mutex_lock(&pd->lock);

	if (front->type	== V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		pd->state &= ~POSEIDON_STATE_ANALOG;

		/* stop the device, and free the URBs */
		usb_transfer_stop(&pd->video_data);
		free_all_urb(&pd->video_data);

		/* stop the firmware */
		send_set_req(pd, PLAY_SERVICE, TLG_TUNE_PLAY_SVC_STOP,
			       &cmd_status);

		pd->file_for_stream = NULL;
		pd->video_data.users--;
	} else if (front->type	== V4L2_BUF_TYPE_VBI_CAPTURE) {
		pd->state &= ~POSEIDON_STATE_VBI;
		pd->vbi_data.front = NULL;
		pd->vbi_data.users--;
	}
	videobuf_stop(&front->q);
	videobuf_mmap_free(&front->q);

	usb_autopm_put_interface(pd->interface);
	mutex_unlock(&pd->lock);

	kfree(front);
	file->private_data = NULL;
	kref_put(&pd->kref, poseidon_delete);
	return 0;
}