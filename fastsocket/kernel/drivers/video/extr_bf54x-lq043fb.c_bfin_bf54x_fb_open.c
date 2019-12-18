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
struct fb_info {struct bfin_bf54xfb_info* par; } ;
struct bfin_bf54xfb_info {int lq043_open_cnt; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EPPI0 ; 
 int EPPI_EN ; 
 int /*<<< orphan*/  SSYNC () ; 
 int bfin_read_EPPI0_CONTROL () ; 
 int /*<<< orphan*/  bfin_write_EPPI0_CONTROL (int) ; 
 int /*<<< orphan*/  config_dma (struct bfin_bf54xfb_info*) ; 
 int /*<<< orphan*/  config_ppi (struct bfin_bf54xfb_info*) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfin_bf54x_fb_open(struct fb_info *info, int user)
{
	struct bfin_bf54xfb_info *fbi = info->par;

	spin_lock(&fbi->lock);
	fbi->lq043_open_cnt++;

	if (fbi->lq043_open_cnt <= 1) {

		bfin_write_EPPI0_CONTROL(0);
		SSYNC();

		config_dma(fbi);
		config_ppi(fbi);

		/* start dma */
		enable_dma(CH_EPPI0);
		bfin_write_EPPI0_CONTROL(bfin_read_EPPI0_CONTROL() | EPPI_EN);
	}

	spin_unlock(&fbi->lock);

	return 0;
}