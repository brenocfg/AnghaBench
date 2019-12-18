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
 int /*<<< orphan*/  upd64031a_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int upd64031a_log_status(struct v4l2_subdev *sd)
{
	v4l2_info(sd, "Status: SA00=0x%02x SA01=0x%02x\n",
			upd64031a_read(sd, 0), upd64031a_read(sd, 1));
	return 0;
}