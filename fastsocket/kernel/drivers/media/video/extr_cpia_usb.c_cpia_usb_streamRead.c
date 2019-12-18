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
typedef  int /*<<< orphan*/  u8 ;
struct usb_cpia {struct framebuf* curbuff; int /*<<< orphan*/  wq_stream; int /*<<< orphan*/  present; } ;
struct framebuf {scalar_t__ status; int length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ FRAME_EMPTY ; 
 scalar_t__ FRAME_READY ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpia_usb_streamRead(void *privdata, u8 *frame, int noblock)
{
	struct usb_cpia *ucpia = (struct usb_cpia *) privdata;
	struct framebuf *mybuff;

	if (!ucpia || !ucpia->present)
		return -1;

	if (ucpia->curbuff->status != FRAME_READY)
		interruptible_sleep_on(&ucpia->wq_stream);
	else
		DBG("Frame already waiting!\n");

	mybuff = ucpia->curbuff;

	if (!mybuff)
		return -1;

	if (mybuff->status != FRAME_READY || mybuff->length < 4) {
		DBG("Something went wrong!\n");
		return -1;
	}

	memcpy(frame, mybuff->data, mybuff->length);
	mybuff->status = FRAME_EMPTY;

/*   DBG("read done, %d bytes, Header: %x/%x, Footer: %x%x%x%x\n",  */
/*       mybuff->length, frame[0], frame[1], */
/*       frame[mybuff->length-4], frame[mybuff->length-3],  */
/*       frame[mybuff->length-2], frame[mybuff->length-1]); */

	return mybuff->length;
}