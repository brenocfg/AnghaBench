#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int pix_tx_time; int line_upd_time; TYPE_1__* extif; scalar_t__ vsync_only; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_tearsync ) (int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HWA742_NDP_CTRL ; 
 TYPE_2__ hwa742 ; 
 int hwa742_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwa742_write_reg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int,int) ; 
 int /*<<< orphan*/  stub3 (int,int) ; 
 int /*<<< orphan*/  stub4 (int,int) ; 

__attribute__((used)) static void enable_tearsync(int y, int width, int height, int screen_height,
			    int force_vsync)
{
	u8 b;

	b = hwa742_read_reg(HWA742_NDP_CTRL);
	b |= 1 << 2;
	hwa742_write_reg(HWA742_NDP_CTRL, b);

	if (likely(hwa742.vsync_only || force_vsync)) {
		hwa742.extif->enable_tearsync(1, 0);
		return;
	}

	if (width * hwa742.pix_tx_time < hwa742.line_upd_time) {
		hwa742.extif->enable_tearsync(1, 0);
		return;
	}

	if ((width * hwa742.pix_tx_time / 1000) * height <
	    (y + height) * (hwa742.line_upd_time / 1000)) {
		hwa742.extif->enable_tearsync(1, 0);
		return;
	}

	hwa742.extif->enable_tearsync(1, y + 1);
}