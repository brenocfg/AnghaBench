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
struct usb_ov511 {int /*<<< orphan*/  maxheight; int /*<<< orphan*/  maxwidth; } ;
struct ov511_frame {int format; int /*<<< orphan*/  bytes_recvd; int /*<<< orphan*/  rawdata; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_DATA_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int /*<<< orphan*/ ) ; 
#define  VIDEO_PALETTE_GREY 130 
#define  VIDEO_PALETTE_YUV420 129 
#define  VIDEO_PALETTE_YUV420P 128 
 scalar_t__ dumppix ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov51x_postprocess_grey (struct usb_ov511*,struct ov511_frame*) ; 
 int /*<<< orphan*/  ov51x_postprocess_yuv420 (struct usb_ov511*,struct ov511_frame*) ; 
 int /*<<< orphan*/  symbolic (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l1_plist ; 

__attribute__((used)) static void
ov51x_postprocess(struct usb_ov511 *ov, struct ov511_frame *frame)
{
	if (dumppix) {
		memset(frame->data, 0,
			MAX_DATA_SIZE(ov->maxwidth, ov->maxheight));
		PDEBUG(4, "Dumping %d bytes", frame->bytes_recvd);
		memcpy(frame->data, frame->rawdata, frame->bytes_recvd);
	} else {
		switch (frame->format) {
		case VIDEO_PALETTE_GREY:
			ov51x_postprocess_grey(ov, frame);
			break;
		case VIDEO_PALETTE_YUV420:
		case VIDEO_PALETTE_YUV420P:
			ov51x_postprocess_yuv420(ov, frame);
			break;
		default:
			err("Cannot convert data to %s",
			    symbolic(v4l1_plist, frame->format));
		}
	}
}