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
struct mfb_info {int count; int /*<<< orphan*/  index; } ;
struct fb_info {int /*<<< orphan*/  var; struct mfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  diu_lock ; 
 int /*<<< orphan*/  fsl_diu_check_var (int /*<<< orphan*/ *,struct fb_info*) ; 
 int fsl_diu_enable_panel (struct fb_info*) ; 
 int fsl_diu_set_par (struct fb_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_diu_open(struct fb_info *info, int user)
{
	struct mfb_info *mfbi = info->par;
	int res = 0;

	spin_lock(&diu_lock);
	mfbi->count++;
	if (mfbi->count == 1) {
		pr_debug("open plane index %d\n", mfbi->index);
		fsl_diu_check_var(&info->var, info);
		res = fsl_diu_set_par(info);
		if (res < 0)
			mfbi->count--;
		else {
			res = fsl_diu_enable_panel(info);
			if (res < 0)
				mfbi->count--;
		}
	}

	spin_unlock(&diu_lock);
	return res;
}