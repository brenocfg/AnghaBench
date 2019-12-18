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
struct TYPE_5__ {size_t baserate; size_t divisor; } ;
struct TYPE_4__ {int /*<<< orphan*/  coarseJump; } ;
struct TYPE_6__ {TYPE_2__ sensorFps; TYPE_1__ flickerControl; } ;
struct sd {int mainsFreq; int freq; TYPE_3__ params; } ;
struct gspca_dev {int /*<<< orphan*/  streaming; } ;
typedef  int __s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ *** flicker_jumps ; 
 int set_flicker (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_setfreq(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int on;

	switch (val) {
	case 0:		/* V4L2_CID_POWER_LINE_FREQUENCY_DISABLED */
		on = 0;
		break;
	case 1:		/* V4L2_CID_POWER_LINE_FREQUENCY_50HZ */
		on = 1;
		sd->mainsFreq = 0;
		break;
	case 2:		/* V4L2_CID_POWER_LINE_FREQUENCY_60HZ */
		on = 1;
		sd->mainsFreq = 1;
		break;
	default:
		return -EINVAL;
	}

	sd->freq = val;
	sd->params.flickerControl.coarseJump =
		flicker_jumps[sd->mainsFreq]
			     [sd->params.sensorFps.baserate]
			     [sd->params.sensorFps.divisor];

	return set_flicker(gspca_dev, on, gspca_dev->streaming);
}