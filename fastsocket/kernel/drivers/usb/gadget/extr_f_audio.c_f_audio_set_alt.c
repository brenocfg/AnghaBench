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
struct usb_request {int /*<<< orphan*/  complete; struct f_audio* context; int /*<<< orphan*/  length; scalar_t__ buf; } ;
struct usb_function {TYPE_1__* config; } ;
struct usb_ep {int /*<<< orphan*/  name; struct f_audio* driver_data; } ;
struct usb_composite_dev {int dummy; } ;
struct f_audio_buf {int /*<<< orphan*/  list; } ;
struct f_audio {int /*<<< orphan*/  playback_work; int /*<<< orphan*/  play_queue; struct f_audio_buf* copy_buf; int /*<<< orphan*/  out_desc; struct usb_ep* out_ep; } ;
struct TYPE_2__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,unsigned int,unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (struct usb_composite_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  audio_buf_size ; 
 struct f_audio_buf* f_audio_buffer_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_audio_complete ; 
 struct f_audio* func_to_audio (struct usb_function*) ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_buf_size ; 
 int req_count ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct usb_request* usb_ep_alloc_request (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_enable (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int usb_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f_audio_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_audio		*audio = func_to_audio(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct usb_ep *out_ep = audio->out_ep;
	struct usb_request *req;
	int i = 0, err = 0;

	DBG(cdev, "intf %d, alt %d\n", intf, alt);

	if (intf == 1) {
		if (alt == 1) {
			usb_ep_enable(out_ep, audio->out_desc);
			out_ep->driver_data = audio;
			audio->copy_buf = f_audio_buffer_alloc(audio_buf_size);

			/*
			 * allocate a bunch of read buffers
			 * and queue them all at once.
			 */
			for (i = 0; i < req_count && err == 0; i++) {
				req = usb_ep_alloc_request(out_ep, GFP_ATOMIC);
				if (req) {
					req->buf = kzalloc(req_buf_size,
							GFP_ATOMIC);
					if (req->buf) {
						req->length = req_buf_size;
						req->context = audio;
						req->complete =
							f_audio_complete;
						err = usb_ep_queue(out_ep,
							req, GFP_ATOMIC);
						if (err)
							ERROR(cdev,
							"%s queue req: %d\n",
							out_ep->name, err);
					} else
						err = -ENOMEM;
				} else
					err = -ENOMEM;
			}

		} else {
			struct f_audio_buf *copy_buf = audio->copy_buf;
			if (copy_buf) {
				list_add_tail(&copy_buf->list,
						&audio->play_queue);
				schedule_work(&audio->playback_work);
			}
		}
	}

	return err;
}