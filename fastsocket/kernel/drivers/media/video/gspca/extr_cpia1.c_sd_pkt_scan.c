#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int colStart; int colEnd; int rowStart; int rowEnd; } ;
struct TYPE_4__ {int videoSize; int subSample; int yuvOrder; } ;
struct TYPE_6__ {TYPE_2__ roi; TYPE_1__ format; } ;
struct sd {int /*<<< orphan*/  fps; int /*<<< orphan*/  cam_exposure; TYPE_3__ params; } ;
struct gspca_dev {int* image; int image_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int MAGIC_0 ; 
 int MAGIC_1 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* Check for SOF */
	if (len >= 64 &&
	    data[0] == MAGIC_0 && data[1] == MAGIC_1 &&
	    data[16] == sd->params.format.videoSize &&
	    data[17] == sd->params.format.subSample &&
	    data[18] == sd->params.format.yuvOrder &&
	    data[24] == sd->params.roi.colStart &&
	    data[25] == sd->params.roi.colEnd &&
	    data[26] == sd->params.roi.rowStart &&
	    data[27] == sd->params.roi.rowEnd) {
		u8 *image;

		atomic_set(&sd->cam_exposure, data[39] * 2);
		atomic_set(&sd->fps, data[41]);

		/* Check for proper EOF for last frame */
		image = gspca_dev->image;
		if (image != NULL &&
		    gspca_dev->image_len > 4 &&
		    image[gspca_dev->image_len - 4] == 0xff &&
		    image[gspca_dev->image_len - 3] == 0xff &&
		    image[gspca_dev->image_len - 2] == 0xff &&
		    image[gspca_dev->image_len - 1] == 0xff)
			gspca_frame_add(gspca_dev, LAST_PACKET,
						NULL, 0);

		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		return;
	}

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}