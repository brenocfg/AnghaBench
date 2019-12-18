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
struct v4l2_querymenu {int id; scalar_t__ name; int /*<<< orphan*/  index; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  CPIA_COMPRESSION_TARGET_FRAMERATE 131 
#define  CPIA_COMPRESSION_TARGET_QUALITY 130 
 int EINVAL ; 
#define  V4L2_CID_COMP_TARGET 129 
#define  V4L2_CID_POWER_LINE_FREQUENCY 128 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int sd_querymenu(struct gspca_dev *gspca_dev,
			struct v4l2_querymenu *menu)
{
	switch (menu->id) {
	case V4L2_CID_POWER_LINE_FREQUENCY:
		switch (menu->index) {
		case 0:		/* V4L2_CID_POWER_LINE_FREQUENCY_DISABLED */
			strcpy((char *) menu->name, "NoFliker");
			return 0;
		case 1:		/* V4L2_CID_POWER_LINE_FREQUENCY_50HZ */
			strcpy((char *) menu->name, "50 Hz");
			return 0;
		case 2:		/* V4L2_CID_POWER_LINE_FREQUENCY_60HZ */
			strcpy((char *) menu->name, "60 Hz");
			return 0;
		}
		break;
	case V4L2_CID_COMP_TARGET:
		switch (menu->index) {
		case CPIA_COMPRESSION_TARGET_QUALITY:
			strcpy((char *) menu->name, "Quality");
			return 0;
		case CPIA_COMPRESSION_TARGET_FRAMERATE:
			strcpy((char *) menu->name, "Framerate");
			return 0;
		}
		break;
	}
	return -EINVAL;
}