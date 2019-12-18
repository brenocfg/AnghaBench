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
struct usb_ov511 {int maxwidth; int maxheight; scalar_t__ buf_state; int /*<<< orphan*/  buf_lock; TYPE_2__* frame; void* tempfbuf; void* rawfbuf; scalar_t__ fbuf; TYPE_1__* sbuf; } ;
struct TYPE_4__ {unsigned char* compbuf; scalar_t__ data; void* tempdata; void* rawdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ BUF_ALLOCATED ; 
 int ENOMEM ; 
 int FRAMES_PER_DESC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_DATA_SIZE (int const,int const) ; 
 int MAX_FRAME_SIZE_PER_DESC ; 
 int MAX_RAW_DATA_SIZE (int const,int const) ; 
 int OV511_NUMFRAMES ; 
 int OV511_NUMSBUF ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov51x_do_dealloc (struct usb_ov511*) ; 
 scalar_t__ rvmalloc (int const) ; 
 void* vmalloc (int const) ; 

__attribute__((used)) static int
ov51x_alloc(struct usb_ov511 *ov)
{
	int i;
	const int w = ov->maxwidth;
	const int h = ov->maxheight;
	const int data_bufsize = OV511_NUMFRAMES * MAX_DATA_SIZE(w, h);
	const int raw_bufsize = OV511_NUMFRAMES * MAX_RAW_DATA_SIZE(w, h);

	PDEBUG(4, "entered");
	mutex_lock(&ov->buf_lock);

	if (ov->buf_state == BUF_ALLOCATED)
		goto out;

	ov->fbuf = rvmalloc(data_bufsize);
	if (!ov->fbuf)
		goto error;

	ov->rawfbuf = vmalloc(raw_bufsize);
	if (!ov->rawfbuf)
		goto error;

	memset(ov->rawfbuf, 0, raw_bufsize);

	ov->tempfbuf = vmalloc(raw_bufsize);
	if (!ov->tempfbuf)
		goto error;

	memset(ov->tempfbuf, 0, raw_bufsize);

	for (i = 0; i < OV511_NUMSBUF; i++) {
		ov->sbuf[i].data = kmalloc(FRAMES_PER_DESC *
			MAX_FRAME_SIZE_PER_DESC, GFP_KERNEL);
		if (!ov->sbuf[i].data)
			goto error;

		PDEBUG(4, "sbuf[%d] @ %p", i, ov->sbuf[i].data);
	}

	for (i = 0; i < OV511_NUMFRAMES; i++) {
		ov->frame[i].data = ov->fbuf + i * MAX_DATA_SIZE(w, h);
		ov->frame[i].rawdata = ov->rawfbuf
		 + i * MAX_RAW_DATA_SIZE(w, h);
		ov->frame[i].tempdata = ov->tempfbuf
		 + i * MAX_RAW_DATA_SIZE(w, h);

		ov->frame[i].compbuf =
		 (unsigned char *) __get_free_page(GFP_KERNEL);
		if (!ov->frame[i].compbuf)
			goto error;

		PDEBUG(4, "frame[%d] @ %p", i, ov->frame[i].data);
	}

	ov->buf_state = BUF_ALLOCATED;
out:
	mutex_unlock(&ov->buf_lock);
	PDEBUG(4, "leaving");
	return 0;
error:
	ov51x_do_dealloc(ov);
	mutex_unlock(&ov->buf_lock);
	PDEBUG(4, "errored");
	return -ENOMEM;
}