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
struct TYPE_4__ {int hue; int colour; } ;
struct uvd {int videosize; int /*<<< orphan*/  dp; TYPE_1__ vpic; } ;
struct usbvideo_frame {int request; int header; int curline; unsigned char* data; int /*<<< orphan*/  deinterlace; } ;
typedef  int /*<<< orphan*/  lineBuffer ;
struct TYPE_5__ {scalar_t__ camera_model; int has_hdr; } ;
typedef  TYPE_2__ ibmcam_t ;
typedef  enum ParseState { ____Placeholder_ParseState } ParseState ;

/* Variables and functions */
 int /*<<< orphan*/  Deinterlace_FillOddLines ; 
 int FLAGS_DISPLAY_HINTS ; 
 int FLAGS_MONOCHROME ; 
#define  HDRSIG_MODEL1_128x96 133 
#define  HDRSIG_MODEL1_176x144 132 
#define  HDRSIG_MODEL1_352x288 131 
 scalar_t__ IBMCAM_MODEL_2 ; 
 scalar_t__ IBMCAM_MODEL_4 ; 
 TYPE_2__* IBMCAM_T (struct uvd*) ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int const,int const) ; 
 int /*<<< orphan*/  RGB24_PUTPIXEL (struct usbvideo_frame*,int,int,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  RingQueue_Dequeue (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 unsigned int RingQueue_GetLength (int /*<<< orphan*/ *) ; 
 int V4L_BYTES_PER_PIXEL ; 
#define  VIDEOSIZE_128x96 130 
#define  VIDEOSIZE_160x120 129 
#define  VIDEOSIZE_176x144 128 
 int VIDEOSIZE_X (int) ; 
 int VIDEOSIZE_Y (int) ; 
 int /*<<< orphan*/  YUV_TO_RGB_BY_THE_BOOK (int,int,int,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int flags ; 
 int hue_correction ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int scan_Continue ; 
 int scan_NextFrame ; 
 int scan_Out ; 

__attribute__((used)) static enum ParseState ibmcam_parse_lines(
	struct uvd *uvd,
	struct usbvideo_frame *frame,
	long *pcopylen)
{
	unsigned char *f;
	ibmcam_t *icam;
	unsigned int len, scanLength, scanHeight, order_uv, order_yc;
	int v4l_linesize; /* V4L line offset */
	const int hue_corr  = (uvd->vpic.hue - 0x8000) >> 10;	/* -32..+31 */
	const int hue2_corr = (hue_correction - 128) / 4;		/* -32..+31 */
	const int ccm = 128; /* Color correction median - see below */
	int y, u, v, i, frame_done=0, color_corr;
	static unsigned char lineBuffer[640*3];
	unsigned const char *chromaLine, *lumaLine;

	assert(uvd != NULL);
	assert(frame != NULL);
	icam = IBMCAM_T(uvd);
	assert(icam != NULL);
	color_corr = (uvd->vpic.colour - 0x8000) >> 8; /* -128..+127 = -ccm..+(ccm-1)*/
	RESTRICT_TO_RANGE(color_corr, -ccm, ccm+1);

	v4l_linesize = VIDEOSIZE_X(frame->request) * V4L_BYTES_PER_PIXEL;

	if (IBMCAM_T(uvd)->camera_model == IBMCAM_MODEL_4) {
		/* Model 4 frame markers do not carry image size identification */
		switch (uvd->videosize) {
		case VIDEOSIZE_128x96:
		case VIDEOSIZE_160x120:
		case VIDEOSIZE_176x144:
			scanLength = VIDEOSIZE_X(uvd->videosize);
			scanHeight = VIDEOSIZE_Y(uvd->videosize);
			break;
		default:
			err("ibmcam_parse_lines: Wrong mode.");
			return scan_Out;
		}
		order_yc = 1;	/* order_yc: true=Yc false=cY ('c'=either U or V) */
		order_uv = 1;	/* Always true in this algorithm */
	} else {
		switch (frame->header) {
		case HDRSIG_MODEL1_128x96:
			scanLength = 128;
			scanHeight = 96;
			order_uv = 1;	/* U Y V Y ... */
			break;
		case HDRSIG_MODEL1_176x144:
			scanLength = 176;
			scanHeight = 144;
			order_uv = 1;	/* U Y V Y ... */
			break;
		case HDRSIG_MODEL1_352x288:
			scanLength = 352;
			scanHeight = 288;
			order_uv = 0;	/* Y V Y V ... */
			break;
		default:
			err("Unknown header signature 00 FF 00 %02lX", frame->header);
			return scan_NextFrame;
		}
		/* order_yc: true=Yc false=cY ('c'=either U or V) */
		order_yc = (IBMCAM_T(uvd)->camera_model == IBMCAM_MODEL_2);
	}

	len = scanLength * 3;
	assert(len <= sizeof(lineBuffer));

	/*
	 * Lines are organized this way:
	 *
	 * I420:
	 * ~~~~
	 * <scanLength->
	 * ___________________________________
	 * |-----Y-----|---UVUVUV...UVUV-----| \
	 * |-----------+---------------------|  \
	 * |<-- 176 -->|<------ 176*2 ------>|  Total 72. lines (interlaced)
	 * |...	   ... |        ...          |  /
	 * |<-- 352 -->|<------ 352*2 ------>|  Total 144. lines (interlaced)
	 * |___________|_____________________| /
	 *  \           \
	 *   lumaLine    chromaLine
	 */

	/* Make sure there's enough data for the entire line */
	if (RingQueue_GetLength(&uvd->dp) < len)
		return scan_Out;

	/* Suck one line out of the ring queue */
	RingQueue_Dequeue(&uvd->dp, lineBuffer, len);

	/*
	 * Make sure that our writing into output buffer
	 * will not exceed the buffer. Mind that we may write
	 * not into current output scanline but in several after
	 * it as well (if we enlarge image vertically.)
	 */
	if ((frame->curline + 2) >= VIDEOSIZE_Y(frame->request))
		return scan_NextFrame;

	/*
	 * Now we are sure that entire line (representing all 'scanLength'
	 * pixels from the camera) is available in the buffer. We
	 * start copying the line left-aligned to the V4L buffer.
	 * If the camera line is shorter then we should pad the V4L
	 * buffer with something (black) to complete the line.
	 */
	assert(frame->data != NULL);
	f = frame->data + (v4l_linesize * frame->curline);

	/*
	 * To obtain chrominance data from the 'chromaLine' use this:
	 *   v = chromaLine[0]; // 0-1:[0], 2-3:[4], 4-5:[8]...
	 *   u = chromaLine[2]; // 0-1:[2], 2-3:[6], 4-5:[10]...
	 *
	 * Indices must be calculated this way:
	 * v_index = (i >> 1) << 2;
	 * u_index = (i >> 1) << 2 + 2;
	 *
	 * where 'i' is the column number [0..VIDEOSIZE_X(frame->request)-1]
	 */
	lumaLine = lineBuffer;
	chromaLine = lineBuffer + scanLength;
	for (i = 0; i < VIDEOSIZE_X(frame->request); i++)
	{
		unsigned char rv, gv, bv;	/* RGB components */

		/* Check for various visual debugging hints (colorized pixels) */
		if ((flags & FLAGS_DISPLAY_HINTS) && (icam->has_hdr)) {
			/*
			 * This is bad and should not happen. This means that
			 * we somehow overshoot the line and encountered new
			 * frame! Obviously our camera/V4L frame size is out
			 * of whack. This cyan dot will help you to figure
			 * out where exactly the new frame arrived.
			 */
			if (icam->has_hdr == 1) {
				bv = 0; /* Yellow marker */
				gv = 0xFF;
				rv = 0xFF;
			} else {
				bv = 0xFF; /* Cyan marker */
				gv = 0xFF;
				rv = 0;
			}
			icam->has_hdr = 0;
			goto make_pixel;
		}

		/*
		 * Check if we are still in range. We may be out of range if our
		 * V4L canvas is wider or taller than the camera "native" image.
		 * Then we quickly fill the remainder of the line with zeros to
		 * make black color and quit the horizontal scanning loop.
		 */
		if (((frame->curline + 2) >= scanHeight) || (i >= scanLength)) {
			const int j = i * V4L_BYTES_PER_PIXEL;
#if USES_IBMCAM_PUTPIXEL
			/* Refresh 'f' because we don't use it much with PUTPIXEL */
			f = frame->data + (v4l_linesize * frame->curline) + j;
#endif
			memset(f, 0, v4l_linesize - j);
			break;
		}

		y = lumaLine[i];
		if (flags & FLAGS_MONOCHROME) /* Use monochrome for debugging */
			rv = gv = bv = y;
		else {
			int off_0, off_2;

			off_0 = (i >> 1) << 2;
			off_2 = off_0 + 2;

			if (order_yc) {
				off_0++;
				off_2++;
			}
			if (!order_uv) {
				off_0 += 2;
				off_2 -= 2;
			}
			u = chromaLine[off_0] + hue_corr;
			v = chromaLine[off_2] + hue2_corr;

			/* Apply color correction */
			if (color_corr != 0) {
				/* Magnify up to 2 times, reduce down to zero saturation */
				u = 128 + ((ccm + color_corr) * (u - 128)) / ccm;
				v = 128 + ((ccm + color_corr) * (v - 128)) / ccm;
			}
			YUV_TO_RGB_BY_THE_BOOK(y, u, v, rv, gv, bv);
		}

	make_pixel:
		/*
		 * The purpose of creating the pixel here, in one,
		 * dedicated place is that we may need to make the
		 * pixel wider and taller than it actually is. This
		 * may be used if camera generates small frames for
		 * sake of frame rate (or any other reason.)
		 *
		 * The output data consists of B, G, R bytes
		 * (in this order).
		 */
#if USES_IBMCAM_PUTPIXEL
		RGB24_PUTPIXEL(frame, i, frame->curline, rv, gv, bv);
#else
		*f++ = bv;
		*f++ = gv;
		*f++ = rv;
#endif
		/*
		 * Typically we do not decide within a legitimate frame
		 * that we want to end the frame. However debugging code
		 * may detect marker of new frame within the data. Then
		 * this condition activates. The 'data' pointer is already
		 * pointing at the new marker, so we'd better leave it as is.
		 */
		if (frame_done)
			break;	/* End scanning of lines */
	}
	/*
	 * Account for number of bytes that we wrote into output V4L frame.
	 * We do it here, after we are done with the scanline, because we
	 * may fill more than one output scanline if we do vertical
	 * enlargement.
	 */
	frame->curline += 2;
	if (pcopylen != NULL)
		*pcopylen += 2 * v4l_linesize;
	frame->deinterlace = Deinterlace_FillOddLines;

	if (frame_done || (frame->curline >= VIDEOSIZE_Y(frame->request)))
		return scan_NextFrame;
	else
		return scan_Continue;
}