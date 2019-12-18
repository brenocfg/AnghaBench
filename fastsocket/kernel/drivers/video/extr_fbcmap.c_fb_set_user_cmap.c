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
typedef  int /*<<< orphan*/  u16 ;
struct fb_info {TYPE_1__* fbops; } ;
struct fb_cmap_user {int len; scalar_t__ start; int /*<<< orphan*/ * transp; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;
struct fb_cmap {scalar_t__ start; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb_setcmap; int /*<<< orphan*/  fb_setcolreg; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fb_alloc_cmap (struct fb_cmap*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (struct fb_cmap*) ; 
 int fb_set_cmap (struct fb_cmap*,struct fb_info*) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  memset (struct fb_cmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

int fb_set_user_cmap(struct fb_cmap_user *cmap, struct fb_info *info)
{
	int rc, size = cmap->len * sizeof(u16);
	struct fb_cmap umap;

	memset(&umap, 0, sizeof(struct fb_cmap));
	rc = fb_alloc_cmap(&umap, cmap->len, cmap->transp != NULL);
	if (rc)
		return rc;
	if (copy_from_user(umap.red, cmap->red, size) ||
	    copy_from_user(umap.green, cmap->green, size) ||
	    copy_from_user(umap.blue, cmap->blue, size) ||
	    (cmap->transp && copy_from_user(umap.transp, cmap->transp, size))) {
		rc = -EFAULT;
		goto out;
	}
	umap.start = cmap->start;
	if (!lock_fb_info(info)) {
		rc = -ENODEV;
		goto out;
	}
	if (cmap->start < 0 || (!info->fbops->fb_setcolreg &&
				!info->fbops->fb_setcmap)) {
		rc = -EINVAL;
		goto out1;
	}
	rc = fb_set_cmap(&umap, info);
out1:
	unlock_fb_info(info);
out:
	fb_dealloc_cmap(&umap);
	return rc;
}