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
struct vc_data {scalar_t__ vc_y; scalar_t__ vc_bottom; int vc_rows; scalar_t__ vc_need_wrap; scalar_t__ vc_size_row; int /*<<< orphan*/  vc_pos; int /*<<< orphan*/  vc_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  notify_write (struct vc_data*,char) ; 
 int /*<<< orphan*/  scrup (struct vc_data*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void lf(struct vc_data *vc)
{
    	/* don't scroll if above bottom of scrolling region, or
	 * if below scrolling region
	 */
    	if (vc->vc_y + 1 == vc->vc_bottom)
		scrup(vc, vc->vc_top, vc->vc_bottom, 1);
	else if (vc->vc_y < vc->vc_rows - 1) {
	    	vc->vc_y++;
		vc->vc_pos += vc->vc_size_row;
	}
	vc->vc_need_wrap = 0;
	notify_write(vc, '\n');
}