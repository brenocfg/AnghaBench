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
struct mfb_info {int /*<<< orphan*/  pseudo_palette; } ;
struct TYPE_2__ {int /*<<< orphan*/  activate; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/ * pseudo_palette; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; TYPE_1__ var; int /*<<< orphan*/ * device; struct mfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_FLAG_DEFAULT ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_diu_ops ; 

__attribute__((used)) static int init_fbinfo(struct fb_info *info)
{
	struct mfb_info *mfbi = info->par;

	info->device = NULL;
	info->var.activate = FB_ACTIVATE_NOW;
	info->fbops = &fsl_diu_ops;
	info->flags = FBINFO_FLAG_DEFAULT;
	info->pseudo_palette = &mfbi->pseudo_palette;

	/* Allocate colormap */
	fb_alloc_cmap(&info->cmap, 16, 0);
	return 0;
}