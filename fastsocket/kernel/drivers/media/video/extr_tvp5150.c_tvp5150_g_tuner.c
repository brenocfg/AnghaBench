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
struct v4l2_tuner {int signal; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int tvp5150_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static int tvp5150_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	int status = tvp5150_read(sd, 0x88);

	vt->signal = ((status & 0x04) && (status & 0x02)) ? 0xffff : 0x0;
	return 0;
}