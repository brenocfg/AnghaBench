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
struct TYPE_3__ {int colour; } ;
struct uvd {int videosize; int /*<<< orphan*/  dp; TYPE_1__ vpic; } ;
struct usbvideo_frame {int request; int curline; unsigned char* data; int /*<<< orphan*/  deinterlace; } ;
typedef  int /*<<< orphan*/  lineBuffer ;
typedef  enum ParseState { ____Placeholder_ParseState } ParseState ;
struct TYPE_4__ {int has_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  Deinterlace_FillOddLines ; 
 int FLAGS_DISPLAY_HINTS ; 
 int FLAGS_MONOCHROME ; 
 TYPE_2__* IBMCAM_T (struct uvd*) ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RGB24_PUTPIXEL (struct usbvideo_frame*,int,int,int,int,int) ; 
 int /*<<< orphan*/  RingQueue_Dequeue (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 unsigned int RingQueue_GetLength (int /*<<< orphan*/ *) ; 
 int V4L_BYTES_PER_PIXEL ; 
#define  VIDEOSIZE_320x240 130 
#define  VIDEOSIZE_352x240 129 
#define  VIDEOSIZE_352x288 128 
 int VIDEOSIZE_X (int) ; 
 int VIDEOSIZE_Y (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int flags ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int scan_Continue ; 
 int scan_NextFrame ; 
 int scan_Out ; 

__attribute__((used)) static enum ParseState ibmcam_model2_320x240_parse_lines(
	struct uvd *uvd,
	struct usbvideo_frame *frame,
	long *pcopylen)
{
	unsigned char *f, *la, *lb;
	unsigned int len;
	int v4l_linesize; /* V4L line offset */
	int i, j, frame_done=0, color_corr;
	int scanLength, scanHeight;
	static unsigned char lineBuffer[352*2];

	switch (uvd->videosize) {
	case VIDEOSIZE_320x240:
	case VIDEOSIZE_352x240:
	case VIDEOSIZE_352x288:
		scanLength = VIDEOSIZE_X(uvd->videosize);
		scanHeight = VIDEOSIZE_Y(uvd->videosize);
		break;
	default:
		err("ibmcam_model2_320x240_parse_lines: Wrong mode.");
		return scan_Out;
	}

	color_corr = (uvd->vpic.colour) >> 8; /* 0..+255 */
	v4l_linesize = VIDEOSIZE_X(frame->request) * V4L_BYTES_PER_PIXEL;

	len = scanLength * 2; /* See explanation above */
	assert(len <= sizeof(lineBuffer));

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

	la = lineBuffer;
	lb = lineBuffer + scanLength;

	/*
	 * Now we are sure that entire line (representing all
	 *         VIDEOSIZE_X(frame->request)
	 * pixels from the camera) is available in the scratch buffer. We
	 * start copying the line left-aligned to the V4L buffer (which
	 * might be larger - not smaller, hopefully). If the camera
	 * line is shorter then we should pad the V4L buffer with something
	 * (black in this case) to complete the line.
	 */
	f = frame->data + (v4l_linesize * frame->curline);

	/* Fill the 2-line strip */
	for (i = 0; i < VIDEOSIZE_X(frame->request); i++) {
		int y, rv, gv, bv;	/* RGB components */

		j = i & (~1);

		/* Check for various visual debugging hints (colorized pixels) */
		if ((flags & FLAGS_DISPLAY_HINTS) && (IBMCAM_T(uvd)->has_hdr)) {
			if (IBMCAM_T(uvd)->has_hdr == 1) {
				bv = 0; /* Yellow marker */
				gv = 0xFF;
				rv = 0xFF;
			} else {
				bv = 0xFF; /* Cyan marker */
				gv = 0xFF;
				rv = 0;
			}
			IBMCAM_T(uvd)->has_hdr = 0;
			goto make_pixel;
		}

		/*
		 * Check if we are still in range. We may be out of range if our
		 * V4L canvas is wider or taller than the camera "native" image.
		 * Then we quickly fill the remainder of the line with zeros to
		 * make black color and quit the horizontal scanning loop.
		 */
		if (((frame->curline + 2) >= scanHeight) || (i >= scanLength)) {
			const int offset = i * V4L_BYTES_PER_PIXEL;
#if USES_IBMCAM_PUTPIXEL
			/* Refresh 'f' because we don't use it much with PUTPIXEL */
			f = frame->data + (v4l_linesize * frame->curline) + offset;
#endif
			memset(f, 0, v4l_linesize - offset);
			break;
		}

		/*
		 * Here I use RA and RB components, one per physical pixel.
		 * This causes fine vertical grid on the picture but may improve
		 * horizontal resolution. If you prefer replicating, use this:
		 *   rv = la[j + 0];   ... or ... rv = la[j + 1];
		 * then the pixel will be replicated.
		 */
		rv = la[i];
		gv = lb[j + 1];
		bv = lb[j + 0];

		y = (rv + gv + bv) / 3; /* Brightness (badly calculated) */

		if (flags & FLAGS_MONOCHROME) /* Use monochrome for debugging */
			rv = gv = bv = y;
		else if (color_corr != 128) {

			/* Calculate difference between color and brightness */
			rv -= y;
			gv -= y;
			bv -= y;

			/* Scale differences */
			rv = (rv * color_corr) / 128;
			gv = (gv * color_corr) / 128;
			bv = (bv * color_corr) / 128;

			/* Reapply brightness */
			rv += y;
			gv += y;
			bv += y;

			/* Watch for overflows */
			RESTRICT_TO_RANGE(rv, 0, 255);
			RESTRICT_TO_RANGE(gv, 0, 255);
			RESTRICT_TO_RANGE(bv, 0, 255);
		}

	make_pixel:
		RGB24_PUTPIXEL(frame, i, frame->curline, rv, gv, bv);
	}
	/*
	 * Account for number of bytes that we wrote into output V4L frame.
	 * We do it here, after we are done with the scanline, because we
	 * may fill more than one output scanline if we do vertical
	 * enlargement.
	 */
	frame->curline += 2;
	*pcopylen += v4l_linesize * 2;
	frame->deinterlace = Deinterlace_FillOddLines;

	if (frame_done || (frame->curline >= VIDEOSIZE_Y(frame->request)))
		return scan_NextFrame;
	else
		return scan_Continue;
}