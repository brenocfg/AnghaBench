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
struct v4l2_jpegcompression {scalar_t__ quality; } ;
struct sd {scalar_t__ quality; int /*<<< orphan*/  jpeg_hdr; } ;
struct gspca_dev {scalar_t__ streaming; } ;

/* Variables and functions */
 scalar_t__ QUALITY_MAX ; 
 scalar_t__ QUALITY_MIN ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sd_set_jcomp(struct gspca_dev *gspca_dev,
			struct v4l2_jpegcompression *jcomp)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (jcomp->quality < QUALITY_MIN)
		sd->quality = QUALITY_MIN;
	else if (jcomp->quality > QUALITY_MAX)
		sd->quality = QUALITY_MAX;
	else
		sd->quality = jcomp->quality;
	if (gspca_dev->streaming)
		jpeg_set_qual(sd->jpeg_hdr, sd->quality);
	return 0;
}