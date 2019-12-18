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
struct vc_data {int vc_x; int vc_cols; int vc_top; int vc_bottom; int vc_rows; int vc_y; int vc_size_row; scalar_t__ vc_need_wrap; scalar_t__ vc_origin; scalar_t__ vc_pos; scalar_t__ vc_decom; } ;

/* Variables and functions */

__attribute__((used)) static void gotoxy(struct vc_data *vc, int new_x, int new_y)
{
	int min_y, max_y;

	if (new_x < 0)
		vc->vc_x = 0;
	else {
		if (new_x >= vc->vc_cols)
			vc->vc_x = vc->vc_cols - 1;
		else
			vc->vc_x = new_x;
	}

 	if (vc->vc_decom) {
		min_y = vc->vc_top;
		max_y = vc->vc_bottom;
	} else {
		min_y = 0;
		max_y = vc->vc_rows;
	}
	if (new_y < min_y)
		vc->vc_y = min_y;
	else if (new_y >= max_y)
		vc->vc_y = max_y - 1;
	else
		vc->vc_y = new_y;
	vc->vc_pos = vc->vc_origin + vc->vc_y * vc->vc_size_row + (vc->vc_x<<1);
	vc->vc_need_wrap = 0;
}