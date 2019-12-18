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
struct uvd {int flags; } ;
struct usbvideo_frame {scalar_t__ deinterlace; unsigned char* data; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 scalar_t__ Deinterlace_FillEvenLines ; 
 scalar_t__ Deinterlace_FillOddLines ; 
 int FLAGS_OVERLAY_STATS ; 
 int V4L_BYTES_PER_PIXEL ; 
 int VIDEOSIZE_X (int /*<<< orphan*/ ) ; 
 int VIDEOSIZE_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int,int,int) ; 
 int /*<<< orphan*/  usbvideo_OverlayStats (struct uvd*,struct usbvideo_frame*) ; 

void usbvideo_DeinterlaceFrame(struct uvd *uvd, struct usbvideo_frame *frame)
{
	if ((uvd == NULL) || (frame == NULL))
		return;

	if ((frame->deinterlace == Deinterlace_FillEvenLines) ||
	    (frame->deinterlace == Deinterlace_FillOddLines))
	{
		const int v4l_linesize = VIDEOSIZE_X(frame->request) * V4L_BYTES_PER_PIXEL;
		int i = (frame->deinterlace == Deinterlace_FillEvenLines) ? 0 : 1;

		for (; i < VIDEOSIZE_Y(frame->request); i += 2) {
			const unsigned char *fs1, *fs2;
			unsigned char *fd;
			int ip, in, j;	/* Previous and next lines */

			/*
			 * Need to average lines before and after 'i'.
			 * If we go out of bounds seeking those lines then
			 * we point back to existing line.
			 */
			ip = i - 1;	/* First, get rough numbers */
			in = i + 1;

			/* Now validate */
			if (ip < 0)
				ip = in;
			if (in >= VIDEOSIZE_Y(frame->request))
				in = ip;

			/* Sanity check */
			if ((ip < 0) || (in < 0) ||
			    (ip >= VIDEOSIZE_Y(frame->request)) ||
			    (in >= VIDEOSIZE_Y(frame->request)))
			{
				err("Error: ip=%d. in=%d. req.height=%ld.",
				    ip, in, VIDEOSIZE_Y(frame->request));
				break;
			}

			/* Now we need to average lines 'ip' and 'in' to produce line 'i' */
			fs1 = frame->data + (v4l_linesize * ip);
			fs2 = frame->data + (v4l_linesize * in);
			fd = frame->data + (v4l_linesize * i);

			/* Average lines around destination */
			for (j=0; j < v4l_linesize; j++) {
				fd[j] = (unsigned char)((((unsigned) fs1[j]) +
							 ((unsigned)fs2[j])) >> 1);
			}
		}
	}

	/* Optionally display statistics on the screen */
	if (uvd->flags & FLAGS_OVERLAY_STATS)
		usbvideo_OverlayStats(uvd, frame);
}