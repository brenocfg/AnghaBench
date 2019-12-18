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
typedef  int u32 ;
struct TYPE_4__ {int* fir_hinc; int* fir_vinc; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int const DISPC_VID1_BASE ; 
 int const DISPC_VID2_BASE ; 
 int const DISPC_VID_ATTRIBUTES ; 
 int const DISPC_VID_FIR ; 
 int const DISPC_VID_SIZE ; 
 int EINVAL ; 
 int ENODEV ; 
 int FLD_MASK (int,int) ; 
 int /*<<< orphan*/  MOD_REG_FLD (int const,int,int) ; 
 int OMAPFB_PLANE_GFX ; 
 unsigned int OMAPFB_PLANE_NUM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 TYPE_2__ dispc ; 
 int dispc_read_reg (int const) ; 
 int /*<<< orphan*/  dispc_write_reg (int const,int) ; 
 int /*<<< orphan*/  enable_lcd_clocks (int) ; 
 int /*<<< orphan*/  set_upsampling_coef_table (int) ; 

__attribute__((used)) static int omap_dispc_set_scale(int plane,
				int orig_width, int orig_height,
				int out_width, int out_height)
{
	const u32 at_reg[]  = { 0, DISPC_VID1_BASE + DISPC_VID_ATTRIBUTES,
				DISPC_VID2_BASE + DISPC_VID_ATTRIBUTES };
	const u32 vs_reg[]  = { 0, DISPC_VID1_BASE + DISPC_VID_SIZE,
				DISPC_VID2_BASE + DISPC_VID_SIZE };
	const u32 fir_reg[] = { 0, DISPC_VID1_BASE + DISPC_VID_FIR,
				DISPC_VID2_BASE + DISPC_VID_FIR };

	u32 l;
	int fir_hinc;
	int fir_vinc;

	if ((unsigned)plane > OMAPFB_PLANE_NUM)
		return -ENODEV;

	if (plane == OMAPFB_PLANE_GFX &&
	    (out_width != orig_width || out_height != orig_height))
		return -EINVAL;

	enable_lcd_clocks(1);
	if (orig_width < out_width) {
		/*
		 * Upsampling.
		 * Currently you can only scale both dimensions in one way.
		 */
		if (orig_height > out_height ||
		    orig_width * 8 < out_width ||
		    orig_height * 8 < out_height) {
			enable_lcd_clocks(0);
			return -EINVAL;
		}
		set_upsampling_coef_table(plane);
	} else if (orig_width > out_width) {
		/* Downsampling not yet supported
		*/

		enable_lcd_clocks(0);
		return -EINVAL;
	}
	if (!orig_width || orig_width == out_width)
		fir_hinc = 0;
	else
		fir_hinc = 1024 * orig_width / out_width;
	if (!orig_height || orig_height == out_height)
		fir_vinc = 0;
	else
		fir_vinc = 1024 * orig_height / out_height;
	dispc.fir_hinc[plane] = fir_hinc;
	dispc.fir_vinc[plane] = fir_vinc;

	MOD_REG_FLD(fir_reg[plane],
		    FLD_MASK(16, 12) | FLD_MASK(0, 12),
		    ((fir_vinc & 4095) << 16) |
		    (fir_hinc & 4095));

	dev_dbg(dispc.fbdev->dev, "out_width %d out_height %d orig_width %d "
		"orig_height %d fir_hinc  %d fir_vinc %d\n",
		out_width, out_height, orig_width, orig_height,
		fir_hinc, fir_vinc);

	MOD_REG_FLD(vs_reg[plane],
		    FLD_MASK(16, 11) | FLD_MASK(0, 11),
		    ((out_height - 1) << 16) | (out_width - 1));

	l = dispc_read_reg(at_reg[plane]);
	l &= ~(0x03 << 5);
	l |= fir_hinc ? (1 << 5) : 0;
	l |= fir_vinc ? (1 << 6) : 0;
	dispc_write_reg(at_reg[plane], l);

	enable_lcd_clocks(0);
	return 0;
}