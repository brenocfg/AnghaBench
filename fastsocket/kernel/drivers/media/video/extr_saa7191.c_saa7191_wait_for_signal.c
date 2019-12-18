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
 int SAA7191_STATUS_HLCK ; 
 int SAA7191_SYNC_COUNT ; 
 int /*<<< orphan*/  SAA7191_SYNC_DELAY ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ saa7191_read_status (struct v4l2_subdev*,int*) ; 

__attribute__((used)) static int saa7191_wait_for_signal(struct v4l2_subdev *sd, u8 *status)
{
	int i = 0;

	dprintk("Checking for signal...\n");

	for (i = 0; i < SAA7191_SYNC_COUNT; i++) {
		if (saa7191_read_status(sd, status))
			return -EIO;

		if (((*status) & SAA7191_STATUS_HLCK) == 0) {
			dprintk("Signal found\n");
			return 0;
		}

		msleep(SAA7191_SYNC_DELAY);
	}

	dprintk("No signal\n");

	return -EBUSY;
}