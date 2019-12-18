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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int SAA7191_STATUS_CODE ; 
 int SAA7191_STATUS_HLCK ; 
 int V4L2_IN_ST_NO_COLOR ; 
 int V4L2_IN_ST_NO_SIGNAL ; 
 scalar_t__ saa7191_read_status (struct v4l2_subdev*,int*) ; 

__attribute__((used)) static int saa7191_g_input_status(struct v4l2_subdev *sd, u32 *status)
{
	u8 status_reg;
	int res = V4L2_IN_ST_NO_SIGNAL;

	if (saa7191_read_status(sd, &status_reg))
		return -EIO;
	if ((status_reg & SAA7191_STATUS_HLCK) == 0)
		res = 0;
	if (!(status_reg & SAA7191_STATUS_CODE))
		res |= V4L2_IN_ST_NO_COLOR;
	*status = res;
	return 0;
}