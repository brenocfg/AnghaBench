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
struct gbe_timing_info {int width; int height; int pll_m; int pll_n; int pll_p; int cfreq; int htotal; int vtotal; int fields_sec; int hblank_start; int vblank_start; int hblank_end; int hsync_start; int hsync_end; int vblank_end; int vsync_start; int vsync_end; } ;
struct gbe_pll_info {int clock_rate; int fvco_min; int fvco_max; } ;
struct fb_var_screeninfo {int pixclock; int xres; int yres; int left_margin; int right_margin; int hsync_len; int upper_margin; int lower_margin; int vsync_len; } ;

/* Variables and functions */
 int EINVAL ; 
 struct gbe_pll_info* gbe_pll_table ; 
 int gbe_revision ; 

__attribute__((used)) static int compute_gbe_timing(struct fb_var_screeninfo *var,
			      struct gbe_timing_info *timing)
{
	int pll_m, pll_n, pll_p, error, best_m, best_n, best_p, best_error;
	int pixclock;
	struct gbe_pll_info *gbe_pll;

	if (gbe_revision < 2)
		gbe_pll = &gbe_pll_table[0];
	else
		gbe_pll = &gbe_pll_table[1];

	/* Determine valid resolution and timing
	 * GBE crystal runs at 20Mhz or 27Mhz
	 * pll_m, pll_n, pll_p define the following frequencies
	 * fvco = pll_m * 20Mhz / pll_n
	 * fout = fvco / (2**pll_p) */
	best_error = 1000000000;
	best_n = best_m = best_p = 0;
	for (pll_p = 0; pll_p < 4; pll_p++)
		for (pll_m = 1; pll_m < 256; pll_m++)
			for (pll_n = 1; pll_n < 64; pll_n++) {
				pixclock = (1000000 / gbe_pll->clock_rate) *
						(pll_n << pll_p) / pll_m;

				error = var->pixclock - pixclock;

				if (error < 0)
					error = -error;

				if (error < best_error &&
				    pll_m / pll_n >
				    gbe_pll->fvco_min / gbe_pll->clock_rate &&
 				    pll_m / pll_n <
				    gbe_pll->fvco_max / gbe_pll->clock_rate) {
					best_error = error;
					best_m = pll_m;
					best_n = pll_n;
					best_p = pll_p;
				}
			}

	if (!best_n || !best_m)
		return -EINVAL;	/* Resolution to high */

	pixclock = (1000000 / gbe_pll->clock_rate) *
		(best_n << best_p) / best_m;

	/* set video timing information */
	if (timing) {
		timing->width = var->xres;
		timing->height = var->yres;
		timing->pll_m = best_m;
		timing->pll_n = best_n;
		timing->pll_p = best_p;
		timing->cfreq = gbe_pll->clock_rate * 1000 * timing->pll_m /
			(timing->pll_n << timing->pll_p);
		timing->htotal = var->left_margin + var->xres +
				var->right_margin + var->hsync_len;
		timing->vtotal = var->upper_margin + var->yres +
				var->lower_margin + var->vsync_len;
		timing->fields_sec = 1000 * timing->cfreq / timing->htotal *
				1000 / timing->vtotal;
		timing->hblank_start = var->xres;
		timing->vblank_start = var->yres;
		timing->hblank_end = timing->htotal;
		timing->hsync_start = var->xres + var->right_margin + 1;
		timing->hsync_end = timing->hsync_start + var->hsync_len;
		timing->vblank_end = timing->vtotal;
		timing->vsync_start = var->yres + var->lower_margin + 1;
		timing->vsync_end = timing->vsync_start + var->vsync_len;
	}

	return pixclock;
}