#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc_data {unsigned int vc_x; unsigned int vc_cols; int vc_video_erase_char; unsigned short vc_attr; int /*<<< orphan*/  vc_y; TYPE_1__* vc_sw; scalar_t__ vc_need_wrap; scalar_t__ vc_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_putc ) (struct vc_data*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* con_bmove ) (struct vc_data*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ DO_UPDATE (struct vc_data*) ; 
 int /*<<< orphan*/  scr_memsetw (unsigned short*,int,unsigned int) ; 
 int /*<<< orphan*/  scr_readw (unsigned short*) ; 
 int /*<<< orphan*/  scr_writew (int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct vc_data*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void delete_char(struct vc_data *vc, unsigned int nr)
{
	unsigned int i = vc->vc_x;
	unsigned short *p = (unsigned short *)vc->vc_pos;

	while (++i <= vc->vc_cols - nr) {
		scr_writew(scr_readw(p+nr), p);
		p++;
	}
	scr_memsetw(p, vc->vc_video_erase_char, nr * 2);
	vc->vc_need_wrap = 0;
	if (DO_UPDATE(vc)) {
		unsigned short oldattr = vc->vc_attr;
		vc->vc_sw->con_bmove(vc, vc->vc_y, vc->vc_x + nr, vc->vc_y, vc->vc_x, 1,
				     vc->vc_cols - vc->vc_x - nr);
		vc->vc_attr = vc->vc_video_erase_char >> 8;
		while (nr--)
			vc->vc_sw->con_putc(vc, vc->vc_video_erase_char, vc->vc_y,
				     vc->vc_cols - 1 - nr);
		vc->vc_attr = oldattr;
	}
}