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
struct TYPE_2__ {int /*<<< orphan*/  frame_num; } ;
struct uvd {int curframe; TYPE_1__ stats; int /*<<< orphan*/  dp; scalar_t__ user_data; } ;
struct usbvideo_frame {scalar_t__ scanstate; int curline; int seqRead_Length; int /*<<< orphan*/  frameState; scalar_t__ data; } ;
struct rgb {int /*<<< orphan*/  b2; int /*<<< orphan*/  g2; int /*<<< orphan*/  r2; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct qcm {int size; int height; int width; scalar_t__ scratch; } ;
struct bayL1 {int /*<<< orphan*/  b; int /*<<< orphan*/  g; } ;
struct bayL0 {int /*<<< orphan*/  r; int /*<<< orphan*/  g; } ;

/* Variables and functions */
 int /*<<< orphan*/  FrameState_Done_Hold ; 
 int /*<<< orphan*/  FrameState_Grabbing ; 
 int /*<<< orphan*/  RING_QUEUE_DEQUEUE_BYTES (int /*<<< orphan*/ *,int) ; 
 int RING_QUEUE_PEEK (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RingQueue_Dequeue (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int RingQueue_GetLength (int /*<<< orphan*/ *) ; 
#define  SIZE_160X120 129 
#define  SIZE_320X240 128 
 scalar_t__ ScanState_Lines ; 
 scalar_t__ ScanState_Scanning ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcm_process_isoc(struct uvd *uvd, struct usbvideo_frame *frame)
{
	struct qcm *cam = (struct qcm *) uvd->user_data;
	int x;
	struct rgb *rgbL0;
	struct rgb *rgbL1;
	struct bayL0 *bayL0;
	struct bayL1 *bayL1;
	int hor,ver,hordel,verdel;
	assert(frame != NULL);

	switch (cam->size) {
	case SIZE_160X120:
		hor = 162; ver = 124; hordel = 1; verdel = 2;
		break;
	case SIZE_320X240:
	default:
		hor = 324; ver = 248; hordel = 2; verdel = 4;
		break;
	}

	if (frame->scanstate == ScanState_Scanning) {
		while (RingQueue_GetLength(&uvd->dp) >=
			 4 + (hor*verdel + hordel)) {
			if ((RING_QUEUE_PEEK(&uvd->dp, 0) == 0x00) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 1) == 0xff) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 2) == 0x00) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 3) == 0xff)) {
				frame->curline = 0;
				frame->scanstate = ScanState_Lines;
				frame->frameState = FrameState_Grabbing;
				RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, 4);
			/*
			* if we're starting, we need to discard the first
			* 4 lines of y bayer data
			* and the first 2 gr elements of x bayer data
			*/
				RING_QUEUE_DEQUEUE_BYTES(&uvd->dp,
							(hor*verdel + hordel));
				break;
			}
			RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, 1);
		}
	}

	if (frame->scanstate == ScanState_Scanning)
		return;

	/* now we can start processing bayer data so long as we have at least
	* 2 lines worth of data. this is the simplest demosaicing method that
	* I could think of. I use each 2x2 bayer element without interpolation
	* to generate 4 rgb pixels.
	*/
	while ( frame->curline < cam->height &&
		(RingQueue_GetLength(&uvd->dp) >= hor*2)) {
		/* get 2 lines of bayer for demosaicing
		 * into 2 lines of RGB */
		RingQueue_Dequeue(&uvd->dp, cam->scratch, hor*2);
		bayL0 = (struct bayL0 *) cam->scratch;
		bayL1 = (struct bayL1 *) (cam->scratch + hor);
		/* frame->curline is the rgb y line */
		rgbL0 = (struct rgb *)
				( frame->data + (cam->width*3*frame->curline));
		/* w/2 because we're already doing 2 pixels */
		rgbL1 = rgbL0 + (cam->width/2);

		for (x=0; x < cam->width; x+=2) {
			rgbL0->r = bayL0->r;
			rgbL0->g = bayL0->g;
			rgbL0->b = bayL1->b;

			rgbL0->r2 = bayL0->r;
			rgbL0->g2 = bayL1->g;
			rgbL0->b2 = bayL1->b;

			rgbL1->r = bayL0->r;
			rgbL1->g = bayL1->g;
			rgbL1->b = bayL1->b;

			rgbL1->r2 = bayL0->r;
			rgbL1->g2 = bayL1->g;
			rgbL1->b2 = bayL1->b;

			rgbL0++;
			rgbL1++;

			bayL0++;
			bayL1++;
		}

		frame->seqRead_Length += cam->width*3*2;
		frame->curline += 2;
	}
	/* See if we filled the frame */
	if (frame->curline == cam->height) {
		frame->frameState = FrameState_Done_Hold;
		frame->curline = 0;
		uvd->curframe = -1;
		uvd->stats.frame_num++;
	}
}