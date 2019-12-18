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
struct dum_ch_setup {int xmin; int xmax; int /*<<< orphan*/  ymax; int /*<<< orphan*/  ymin; } ;
struct disp_window {int xmin_l; int xmin_h; int xmax_l; int xmax_h; int /*<<< orphan*/  ymax; int /*<<< orphan*/  ymin; } ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static void build_disp_window(struct dum_ch_setup * ch_setup, struct disp_window * dw)
{
	dw->ymin = ch_setup->ymin;
	dw->ymax = ch_setup->ymax;
	dw->xmin_l = ch_setup->xmin & 0xFF;
	dw->xmin_h = (ch_setup->xmin & BIT(8)) >> 8;
	dw->xmax_l = ch_setup->xmax & 0xFF;
	dw->xmax_h = (ch_setup->xmax & BIT(8)) >> 8;
}