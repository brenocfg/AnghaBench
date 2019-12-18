#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_request {scalar_t__ actual; int /*<<< orphan*/  buf; struct f_audio* context; } ;
struct usb_ep {int /*<<< orphan*/  name; } ;
struct usb_composite_dev {int dummy; } ;
struct f_audio_buf {scalar_t__ actual; scalar_t__ buf; int /*<<< orphan*/  list; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_6__ {TYPE_2__ func; } ;
struct f_audio {struct f_audio_buf* copy_buf; int /*<<< orphan*/  playback_work; int /*<<< orphan*/  play_queue; TYPE_3__ card; } ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (struct usb_composite_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ audio_buf_size ; 
 struct f_audio_buf* f_audio_buffer_alloc (scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int usb_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f_audio_out_ep_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct f_audio *audio = req->context;
	struct usb_composite_dev *cdev = audio->card.func.config->cdev;
	struct f_audio_buf *copy_buf = audio->copy_buf;
	int err;

	if (!copy_buf)
		return -EINVAL;

	/* Copy buffer is full, add it to the play_queue */
	if (audio_buf_size - copy_buf->actual < req->actual) {
		list_add_tail(&copy_buf->list, &audio->play_queue);
		schedule_work(&audio->playback_work);
		copy_buf = f_audio_buffer_alloc(audio_buf_size);
		if (copy_buf < 0)
			return -ENOMEM;
	}

	memcpy(copy_buf->buf + copy_buf->actual, req->buf, req->actual);
	copy_buf->actual += req->actual;
	audio->copy_buf = copy_buf;

	err = usb_ep_queue(ep, req, GFP_ATOMIC);
	if (err)
		ERROR(cdev, "%s queue req: %d\n", ep->name, err);

	return 0;

}