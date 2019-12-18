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
struct mfb_info {scalar_t__ count; int /*<<< orphan*/  index; } ;
struct fb_info {struct mfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  diu_lock ; 
 int fsl_diu_disable_panel (struct fb_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_diu_release(struct fb_info *info, int user)
{
	struct mfb_info *mfbi = info->par;
	int res = 0;

	spin_lock(&diu_lock);
	mfbi->count--;
	if (mfbi->count == 0) {
		pr_debug("release plane index %d\n", mfbi->index);
		res = fsl_diu_disable_panel(info);
		if (res < 0)
			mfbi->count++;
	}
	spin_unlock(&diu_lock);
	return res;
}