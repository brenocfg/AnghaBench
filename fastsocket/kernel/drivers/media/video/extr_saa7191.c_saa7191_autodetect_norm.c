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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int SAA7191_STATUS_FIDT ; 
 int SAA7191_STATUS_HLCK ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ saa7191_read_status (struct v4l2_subdev*,int*) ; 
 int saa7191_s_std (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7191_autodetect_norm(struct v4l2_subdev *sd)
{
	u8 status;

	dprintk("SAA7191 signal auto-detection...\n");

	dprintk("Reading status...\n");

	if (saa7191_read_status(sd, &status))
		return -EIO;

	dprintk("Checking for signal...\n");

	/* no signal ? */
	if (status & SAA7191_STATUS_HLCK) {
		dprintk("No signal\n");
		return -EBUSY;
	}

	dprintk("Signal found\n");

	if (status & SAA7191_STATUS_FIDT) {
		/* 60hz signal -> NTSC */
		dprintk("NTSC\n");
		return saa7191_s_std(sd, V4L2_STD_NTSC);
	} else {
		/* 50hz signal -> PAL */
		dprintk("PAL\n");
		return saa7191_s_std(sd, V4L2_STD_PAL);
	}
}