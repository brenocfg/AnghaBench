#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_se401 {size_t scratch_use; scalar_t__ nullpackets; scalar_t__ format; int cheight; int cwidth; TYPE_2__* frame; scalar_t__ enhance; TYPE_1__* dev; TYPE_3__* scratch; int /*<<< orphan*/  wq; scalar_t__ streaming; } ;
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_6__ {scalar_t__ grabstate; int /*<<< orphan*/  data; int /*<<< orphan*/  curpix; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BUFFER_BUSY ; 
 scalar_t__ BUFFER_READY ; 
 scalar_t__ BUFFER_UNUSED ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ FMT_JANGGU ; 
 scalar_t__ FRAME_DONE ; 
 scalar_t__ FRAME_ERROR ; 
 scalar_t__ FRAME_GRABBING ; 
 scalar_t__ FRAME_READY ; 
 int SE401_MAX_ERRORS ; 
 scalar_t__ SE401_MAX_NULLPACKETS ; 
 size_t SE401_NUMSCRATCH ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  decode_JangGu (struct usb_se401*,TYPE_3__*) ; 
 int /*<<< orphan*/  decode_bayer (struct usb_se401*,TYPE_3__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  enhance_picture (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  se401_start_stream (struct usb_se401*) ; 
 int /*<<< orphan*/  se401_stop_stream (struct usb_se401*) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_interruptible (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int se401_newframe(struct usb_se401 *se401, int framenr)
{
	DECLARE_WAITQUEUE(wait, current);
	int errors = 0;

	while (se401->streaming &&
	    (se401->frame[framenr].grabstate == FRAME_READY ||
	     se401->frame[framenr].grabstate == FRAME_GRABBING)) {
		if (!se401->frame[framenr].curpix)
			errors++;

		wait_interruptible(
		    se401->scratch[se401->scratch_use].state != BUFFER_READY,
						    &se401->wq, &wait);
		if (se401->nullpackets > SE401_MAX_NULLPACKETS) {
			se401->nullpackets = 0;
			dev_info(&se401->dev->dev,
			 "too many null length packets, restarting capture\n");
			se401_stop_stream(se401);
			se401_start_stream(se401);
		} else {
			if (se401->scratch[se401->scratch_use].state !=
								BUFFER_READY) {
				se401->frame[framenr].grabstate = FRAME_ERROR;
				return -EIO;
			}
			se401->scratch[se401->scratch_use].state = BUFFER_BUSY;
			if (se401->format == FMT_JANGGU)
				decode_JangGu(se401,
					&se401->scratch[se401->scratch_use]);
			else
				decode_bayer(se401,
					&se401->scratch[se401->scratch_use]);

			se401->scratch[se401->scratch_use].state =
							BUFFER_UNUSED;
			se401->scratch_use++;
			if (se401->scratch_use >= SE401_NUMSCRATCH)
				se401->scratch_use = 0;
			if (errors > SE401_MAX_ERRORS) {
				errors = 0;
				dev_info(&se401->dev->dev,
				      "too many errors, restarting capture\n");
				se401_stop_stream(se401);
				se401_start_stream(se401);
			}
		}
	}

	if (se401->frame[framenr].grabstate == FRAME_DONE)
		if (se401->enhance)
			enhance_picture(se401->frame[framenr].data,
					se401->cheight * se401->cwidth * 3);
	return 0;
}