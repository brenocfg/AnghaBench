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
struct fb_info {struct bfin_t350mcqbfb_info* par; } ;
struct bfin_t350mcqbfb_info {int lq043_open_cnt; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_PPI ; 
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  bfin_t350mcqb_config_dma (struct bfin_t350mcqbfb_info*) ; 
 int /*<<< orphan*/  bfin_t350mcqb_config_ppi (struct bfin_t350mcqbfb_info*) ; 
 int /*<<< orphan*/  bfin_t350mcqb_disable_ppi () ; 
 int /*<<< orphan*/  bfin_t350mcqb_enable_ppi () ; 
 int /*<<< orphan*/  bfin_t350mcqb_init_timers () ; 
 int /*<<< orphan*/  bfin_t350mcqb_start_timers () ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfin_t350mcqb_fb_open(struct fb_info *info, int user)
{
	struct bfin_t350mcqbfb_info *fbi = info->par;

	spin_lock(&fbi->lock);
	fbi->lq043_open_cnt++;

	if (fbi->lq043_open_cnt <= 1) {

		bfin_t350mcqb_disable_ppi();
		SSYNC();

		bfin_t350mcqb_config_dma(fbi);
		bfin_t350mcqb_config_ppi(fbi);
		bfin_t350mcqb_init_timers();

		/* start dma */
		enable_dma(CH_PPI);
		bfin_t350mcqb_enable_ppi();
		bfin_t350mcqb_start_timers();
	}

	spin_unlock(&fbi->lock);

	return 0;
}