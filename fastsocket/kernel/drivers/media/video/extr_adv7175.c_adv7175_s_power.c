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
 int /*<<< orphan*/  adv7175_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static int adv7175_s_power(struct v4l2_subdev *sd, int on)
{
	if (on)
		adv7175_write(sd, 0x01, 0x00);
	else
		adv7175_write(sd, 0x01, 0x78);

	return 0;
}