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
struct bfin_t350mcqbfb_info {scalar_t__ lq043_open_cnt; int /*<<< orphan*/  lock; scalar_t__ lq043_mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_PPI ; 
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  bfin_t350mcqb_disable_ppi () ; 
 int /*<<< orphan*/  bfin_t350mcqb_stop_timers () ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bfin_t350mcqb_fb_release(struct fb_info *info, int user)
{
	struct bfin_t350mcqbfb_info *fbi = info->par;

	spin_lock(&fbi->lock);

	fbi->lq043_open_cnt--;
	fbi->lq043_mmap = 0;

	if (fbi->lq043_open_cnt <= 0) {
		bfin_t350mcqb_disable_ppi();
		SSYNC();
		disable_dma(CH_PPI);
		bfin_t350mcqb_stop_timers();
	}

	spin_unlock(&fbi->lock);

	return 0;
}