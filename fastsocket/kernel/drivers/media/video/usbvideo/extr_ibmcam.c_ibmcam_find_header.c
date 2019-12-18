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
struct TYPE_6__ {int /*<<< orphan*/  header_count; } ;
struct uvd {scalar_t__ curframe; int debug; TYPE_2__ stats; TYPE_1__* dev; int /*<<< orphan*/  dp; int /*<<< orphan*/  videosize; struct usbvideo_frame* frame; } ;
struct usbvideo_frame {int header; scalar_t__ curline; int /*<<< orphan*/  scanstate; } ;
struct TYPE_7__ {int has_hdr; int camera_model; } ;
typedef  TYPE_3__ ibmcam_t ;
typedef  enum ParseState { ____Placeholder_ParseState } ParseState ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FLAGS_FORCE_TESTPATTERN ; 
 int HDRSIG_MODEL1_128x96 ; 
 int HDRSIG_MODEL1_176x144 ; 
 int HDRSIG_MODEL1_352x288 ; 
#define  IBMCAM_MODEL_1 132 
#define  IBMCAM_MODEL_2 131 
#define  IBMCAM_MODEL_3 130 
#define  IBMCAM_MODEL_4 129 
 TYPE_3__* IBMCAM_T (struct uvd*) ; 
 int /*<<< orphan*/  RING_QUEUE_DEQUEUE_BYTES (int /*<<< orphan*/ *,int const) ; 
 int RING_QUEUE_PEEK (int /*<<< orphan*/ *,int) ; 
 int const RingQueue_GetLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanState_Lines ; 
 scalar_t__ USBVIDEO_NUMFRAMES ; 
#define  VIDEOSIZE_176x144 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  err (char*,scalar_t__) ; 
 int flags ; 
 int scan_Continue ; 
 int scan_EndParse ; 
 int scan_NextFrame ; 
 int /*<<< orphan*/  usbvideo_TestPattern (struct uvd*,int,int) ; 

__attribute__((used)) static enum ParseState ibmcam_find_header(struct uvd *uvd) /* FIXME: Add frame here */
{
	struct usbvideo_frame *frame;
	ibmcam_t *icam;

	if ((uvd->curframe) < 0 || (uvd->curframe >= USBVIDEO_NUMFRAMES)) {
		err("ibmcam_find_header: Illegal frame %d.", uvd->curframe);
		return scan_EndParse;
	}
	icam = IBMCAM_T(uvd);
	assert(icam != NULL);
	frame = &uvd->frame[uvd->curframe];
	icam->has_hdr = 0;
	switch (icam->camera_model) {
	case IBMCAM_MODEL_1:
	{
		const int marker_len = 4;
		while (RingQueue_GetLength(&uvd->dp) >= marker_len) {
			if ((RING_QUEUE_PEEK(&uvd->dp, 0) == 0x00) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 1) == 0xFF) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 2) == 0x00))
			{
#if 0				/* This code helps to detect new frame markers */
				dev_info(&uvd->dev->dev,
					 "Header sig: 00 FF 00 %02X\n",
					 RING_QUEUE_PEEK(&uvd->dp, 3));
#endif
				frame->header = RING_QUEUE_PEEK(&uvd->dp, 3);
				if ((frame->header == HDRSIG_MODEL1_128x96) ||
				    (frame->header == HDRSIG_MODEL1_176x144) ||
				    (frame->header == HDRSIG_MODEL1_352x288))
				{
#if 0
					dev_info(&uvd->dev->dev,
						 "Header found.\n");
#endif
					RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, marker_len);
					icam->has_hdr = 1;
					break;
				}
			}
			/* If we are still here then this doesn't look like a header */
			RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, 1);
		}
		break;
	}
	case IBMCAM_MODEL_2:
case IBMCAM_MODEL_4:
	{
		int marker_len = 0;
		switch (uvd->videosize) {
		case VIDEOSIZE_176x144:
			marker_len = 10;
			break;
		default:
			marker_len = 2;
			break;
		}
		while (RingQueue_GetLength(&uvd->dp) >= marker_len) {
			if ((RING_QUEUE_PEEK(&uvd->dp, 0) == 0x00) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 1) == 0xFF))
			{
#if 0
				dev_info(&uvd->dev->dev, "Header found.\n");
#endif
				RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, marker_len);
				icam->has_hdr = 1;
				frame->header = HDRSIG_MODEL1_176x144;
				break;
			}
			/* If we are still here then this doesn't look like a header */
			RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, 1);
		}
		break;
	}
	case IBMCAM_MODEL_3:
	{	/*
		 * Headers: (one precedes every frame). nc=no compression,
		 * bq=best quality bf=best frame rate.
		 *
		 * 176x144: 00 FF 02 { 0A=nc CA=bq EA=bf }
		 * 320x240: 00 FF 02 { 08=nc 28=bq 68=bf }
		 * 640x480: 00 FF 03 { 08=nc 28=bq 68=bf }
		 *
		 * Bytes '00 FF' seem to indicate header. Other two bytes
		 * encode the frame type. This is a set of bit fields that
		 * encode image size, compression type etc. These fields
		 * do NOT contain frame number because all frames carry
		 * the same header.
		 */
		const int marker_len = 4;
		while (RingQueue_GetLength(&uvd->dp) >= marker_len) {
			if ((RING_QUEUE_PEEK(&uvd->dp, 0) == 0x00) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 1) == 0xFF) &&
			    (RING_QUEUE_PEEK(&uvd->dp, 2) != 0xFF))
			{
				/*
				 * Combine 2 bytes of frame type into one
				 * easy to use value
				 */
				unsigned long byte3, byte4;

				byte3 = RING_QUEUE_PEEK(&uvd->dp, 2);
				byte4 = RING_QUEUE_PEEK(&uvd->dp, 3);
				frame->header = (byte3 << 8) | byte4;
#if 0
				dev_info(&uvd->dev->dev, "Header found.\n");
#endif
				RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, marker_len);
				icam->has_hdr = 1;
				break;
			}
			/* If we are still here then this doesn't look like a header */
			RING_QUEUE_DEQUEUE_BYTES(&uvd->dp, 1);
		}
		break;
	}
	default:
		break;
	}
	if (!icam->has_hdr) {
		if (uvd->debug > 2)
			dev_info(&uvd->dev->dev,
				 "Skipping frame, no header\n");
		return scan_EndParse;
	}

	/* Header found */
	icam->has_hdr = 1;
	uvd->stats.header_count++;
	frame->scanstate = ScanState_Lines;
	frame->curline = 0;

	if (flags & FLAGS_FORCE_TESTPATTERN) {
		usbvideo_TestPattern(uvd, 1, 1);
		return scan_NextFrame;
	}
	return scan_Continue;
}