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
typedef  int u32 ;
struct lcd_ctrl_config {scalar_t__ bpp; int fdd; int /*<<< orphan*/  raster_order; TYPE_1__* p_disp_panel; int /*<<< orphan*/  ac_bias_intrpt; int /*<<< orphan*/  ac_bias; int /*<<< orphan*/  dma_burst_sz; } ;
struct da8xx_panel {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  hfp; int /*<<< orphan*/  hsw; int /*<<< orphan*/  hbp; int /*<<< orphan*/  vfp; int /*<<< orphan*/  vsw; int /*<<< orphan*/  vbp; scalar_t__ invert_pxl_clk; int /*<<< orphan*/  pxl_clk; } ;
struct da8xx_fb_par {int dummy; } ;
struct TYPE_2__ {scalar_t__ panel_type; scalar_t__ max_bpp; scalar_t__ min_bpp; } ;

/* Variables and functions */
 int EINVAL ; 
 int LCD_CLK_DIVISOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_CTRL_REG ; 
 int LCD_INVERT_PIXEL_CLOCK ; 
 int /*<<< orphan*/  LCD_RASTER_CTRL_REG ; 
 int LCD_RASTER_MODE ; 
 int /*<<< orphan*/  LCD_RASTER_TIMING_2_REG ; 
 scalar_t__ QVGA ; 
 int /*<<< orphan*/  lcd_cfg_ac_bias (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lcd_cfg_display (struct lcd_ctrl_config const*) ; 
 int lcd_cfg_dma (int /*<<< orphan*/ ) ; 
 int lcd_cfg_frame_buffer (struct da8xx_fb_par*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_cfg_horizontal_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_cfg_vertical_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_reset (struct da8xx_fb_par*) ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcd_init(struct da8xx_fb_par *par, const struct lcd_ctrl_config *cfg,
		struct da8xx_panel *panel)
{
	u32 bpp;
	int ret = 0;

	lcd_reset(par);

	/* Configure the LCD clock divisor. */
	lcdc_write(LCD_CLK_DIVISOR(panel->pxl_clk) |
			(LCD_RASTER_MODE & 0x1), LCD_CTRL_REG);

	if (panel->invert_pxl_clk)
		lcdc_write((lcdc_read(LCD_RASTER_TIMING_2_REG) |
			LCD_INVERT_PIXEL_CLOCK), LCD_RASTER_TIMING_2_REG);
	else
		lcdc_write((lcdc_read(LCD_RASTER_TIMING_2_REG) &
			~LCD_INVERT_PIXEL_CLOCK), LCD_RASTER_TIMING_2_REG);

	/* Configure the DMA burst size. */
	ret = lcd_cfg_dma(cfg->dma_burst_sz);
	if (ret < 0)
		return ret;

	/* Configure the AC bias properties. */
	lcd_cfg_ac_bias(cfg->ac_bias, cfg->ac_bias_intrpt);

	/* Configure the vertical and horizontal sync properties. */
	lcd_cfg_vertical_sync(panel->vbp, panel->vsw, panel->vfp);
	lcd_cfg_horizontal_sync(panel->hbp, panel->hsw, panel->hfp);

	/* Configure for disply */
	ret = lcd_cfg_display(cfg);
	if (ret < 0)
		return ret;

	if (QVGA != cfg->p_disp_panel->panel_type)
		return -EINVAL;

	if (cfg->bpp <= cfg->p_disp_panel->max_bpp &&
	    cfg->bpp >= cfg->p_disp_panel->min_bpp)
		bpp = cfg->bpp;
	else
		bpp = cfg->p_disp_panel->max_bpp;
	if (bpp == 12)
		bpp = 16;
	ret = lcd_cfg_frame_buffer(par, (unsigned int)panel->width,
				(unsigned int)panel->height, bpp,
				cfg->raster_order);
	if (ret < 0)
		return ret;

	/* Configure FDD */
	lcdc_write((lcdc_read(LCD_RASTER_CTRL_REG) & 0xfff00fff) |
		       (cfg->fdd << 12), LCD_RASTER_CTRL_REG);

	return 0;
}