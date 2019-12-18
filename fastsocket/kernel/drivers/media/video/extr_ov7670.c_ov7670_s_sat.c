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
struct ov7670_info {int sat; } ;

/* Variables and functions */
 int CMATRIX_LEN ; 
 int /*<<< orphan*/  ov7670_calc_cmatrix (struct ov7670_info*,int*) ; 
 int ov7670_store_cmatrix (struct v4l2_subdev*,int*) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_s_sat(struct v4l2_subdev *sd, int value)
{
	struct ov7670_info *info = to_state(sd);
	int matrix[CMATRIX_LEN];
	int ret;

	info->sat = value;
	ov7670_calc_cmatrix(info, matrix);
	ret = ov7670_store_cmatrix(sd, matrix);
	return ret;
}