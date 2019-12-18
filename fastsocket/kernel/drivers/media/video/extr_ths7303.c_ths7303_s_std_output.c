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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int ths7303_setvalue (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ths7303_s_std_output(struct v4l2_subdev *sd, v4l2_std_id norm)
{
	return ths7303_setvalue(sd, norm);
}