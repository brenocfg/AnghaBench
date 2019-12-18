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
struct atmel_lcdfb_info {scalar_t__ lcdcon_is_backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_LCDC_CONTRAST_CTR ; 
 int /*<<< orphan*/  ATMEL_LCDC_CONTRAST_VAL ; 
 int /*<<< orphan*/  ATMEL_LCDC_CVAL_DEFAULT ; 
 int /*<<< orphan*/  contrast_ctr ; 
 int /*<<< orphan*/  init_backlight (struct atmel_lcdfb_info*) ; 
 int /*<<< orphan*/  lcdc_writel (struct atmel_lcdfb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_contrast(struct atmel_lcdfb_info *sinfo)
{
	/* have some default contrast/backlight settings */
	lcdc_writel(sinfo, ATMEL_LCDC_CONTRAST_CTR, contrast_ctr);
	lcdc_writel(sinfo, ATMEL_LCDC_CONTRAST_VAL, ATMEL_LCDC_CVAL_DEFAULT);

	if (sinfo->lcdcon_is_backlight)
		init_backlight(sinfo);
}