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
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*) ; 
 int /*<<< orphan*/  vpx3220_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static int vpx3220_s_stream(struct v4l2_subdev *sd, int enable)
{
	v4l2_dbg(1, debug, sd, "s_stream %s\n", enable ? "on" : "off");

	vpx3220_write(sd, 0xf2, (enable ? 0x1b : 0x00));
	return 0;
}