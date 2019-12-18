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
typedef  int /*<<< orphan*/  v4l2_std_id ;
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_STAT ; 
 int V4L2_IN_ST_NO_COLOR ; 
 int V4L2_IN_ST_NO_SIGNAL ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 
 int ks0127_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks0127_status(struct v4l2_subdev *sd, u32 *pstatus, v4l2_std_id *pstd)
{
	int stat = V4L2_IN_ST_NO_SIGNAL;
	u8 status;
	v4l2_std_id std = V4L2_STD_ALL;

	status = ks0127_read(sd, KS_STAT);
	if (!(status & 0x20))		 /* NOVID not set */
		stat = 0;
	if (!(status & 0x01))		      /* CLOCK set */
		stat |= V4L2_IN_ST_NO_COLOR;
	if ((status & 0x08))		   /* PALDET set */
		std = V4L2_STD_PAL;
	else
		std = V4L2_STD_NTSC;
	if (pstd)
		*pstd = std;
	if (pstatus)
		*pstatus = stat;
	return 0;
}