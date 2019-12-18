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
struct v4l2_sliced_vbi_format {int** service_lines; int service_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct v4l2_sliced_vbi_format*,int /*<<< orphan*/ ,int) ; 
 int tvp5150_get_vbi (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vbi_ram_default ; 

__attribute__((used)) static int tvp5150_g_sliced_fmt(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *svbi)
{
	int i, mask = 0;

	memset(svbi, 0, sizeof(*svbi));

	for (i = 0; i <= 23; i++) {
		svbi->service_lines[0][i] =
			tvp5150_get_vbi(sd, vbi_ram_default, i);
		mask |= svbi->service_lines[0][i];
	}
	svbi->service_set = mask;
	return 0;
}