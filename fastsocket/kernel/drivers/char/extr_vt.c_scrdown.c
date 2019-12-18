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
struct vc_data {unsigned int vc_rows; unsigned int vc_size_row; int vc_cols; int /*<<< orphan*/  vc_video_erase_char; scalar_t__ vc_origin; TYPE_1__* vc_sw; } ;
struct TYPE_2__ {scalar_t__ (* con_scroll ) (struct vc_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ CON_IS_VISIBLE (struct vc_data*) ; 
 int /*<<< orphan*/  SM_DOWN ; 
 int /*<<< orphan*/  scr_memmovew (unsigned short*,unsigned short*,unsigned int) ; 
 int /*<<< orphan*/  scr_memsetw (unsigned short*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct vc_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void scrdown(struct vc_data *vc, unsigned int t, unsigned int b, int nr)
{
	unsigned short *s;
	unsigned int step;

	if (t+nr >= b)
		nr = b - t - 1;
	if (b > vc->vc_rows || t >= b || nr < 1)
		return;
	if (CON_IS_VISIBLE(vc) && vc->vc_sw->con_scroll(vc, t, b, SM_DOWN, nr))
		return;
	s = (unsigned short *)(vc->vc_origin + vc->vc_size_row * t);
	step = vc->vc_cols * nr;
	scr_memmovew(s + step, s, (b - t - nr) * vc->vc_size_row);
	scr_memsetw(s, vc->vc_video_erase_char, 2 * step);
}