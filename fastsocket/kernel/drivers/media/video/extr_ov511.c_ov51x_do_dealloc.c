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
struct usb_ov511 {int /*<<< orphan*/  buf_state; TYPE_2__* frame; TYPE_1__* sbuf; int /*<<< orphan*/ * tempfbuf; int /*<<< orphan*/ * rawfbuf; int /*<<< orphan*/ * fbuf; int /*<<< orphan*/  maxheight; int /*<<< orphan*/  maxwidth; } ;
struct TYPE_4__ {int /*<<< orphan*/ * compbuf; int /*<<< orphan*/ * tempdata; int /*<<< orphan*/ * rawdata; int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_NOT_ALLOCATED ; 
 int MAX_DATA_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OV511_NUMFRAMES ; 
 int OV511_NUMSBUF ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ov51x_do_dealloc(struct usb_ov511 *ov)
{
	int i;
	PDEBUG(4, "entered");

	if (ov->fbuf) {
		rvfree(ov->fbuf, OV511_NUMFRAMES
		       * MAX_DATA_SIZE(ov->maxwidth, ov->maxheight));
		ov->fbuf = NULL;
	}

	vfree(ov->rawfbuf);
	ov->rawfbuf = NULL;

	vfree(ov->tempfbuf);
	ov->tempfbuf = NULL;

	for (i = 0; i < OV511_NUMSBUF; i++) {
		kfree(ov->sbuf[i].data);
		ov->sbuf[i].data = NULL;
	}

	for (i = 0; i < OV511_NUMFRAMES; i++) {
		ov->frame[i].data = NULL;
		ov->frame[i].rawdata = NULL;
		ov->frame[i].tempdata = NULL;
		if (ov->frame[i].compbuf) {
			free_page((unsigned long) ov->frame[i].compbuf);
			ov->frame[i].compbuf = NULL;
		}
	}

	PDEBUG(4, "buffer memory deallocated");
	ov->buf_state = BUF_NOT_ALLOCATED;
	PDEBUG(4, "leaving");
}