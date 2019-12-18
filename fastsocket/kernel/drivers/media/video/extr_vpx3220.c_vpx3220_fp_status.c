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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 unsigned int VPX_TIMEOUT_COUNT ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned char vpx3220_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static int vpx3220_fp_status(struct v4l2_subdev *sd)
{
	unsigned char status;
	unsigned int i;

	for (i = 0; i < VPX_TIMEOUT_COUNT; i++) {
		status = vpx3220_read(sd, 0x29);

		if (!(status & 4))
			return 0;

		udelay(10);

		if (need_resched())
			cond_resched();
	}

	return -1;
}