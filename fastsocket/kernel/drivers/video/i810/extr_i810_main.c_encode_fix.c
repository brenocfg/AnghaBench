#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  physical; } ;
struct i810fb_par {int /*<<< orphan*/  mmio_start_phys; int /*<<< orphan*/  pitch; TYPE_1__ fb; } ;
struct TYPE_4__ {int bits_per_pixel; int /*<<< orphan*/  nonstd; } ;
struct fb_info {TYPE_2__ var; int /*<<< orphan*/  mm_lock; struct i810fb_par* par; } ;
struct fb_fix_screeninfo {int xpanstep; int ypanstep; int /*<<< orphan*/  accel; int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio_start; int /*<<< orphan*/  line_length; scalar_t__ ywrapstep; int /*<<< orphan*/  visual; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FB_ACCEL_I810 ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  MMIO_SIZE ; 
 int /*<<< orphan*/  memset (struct fb_fix_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int encode_fix(struct fb_fix_screeninfo *fix, struct fb_info *info)
{
	struct i810fb_par *par = info->par;

    	memset(fix, 0, sizeof(struct fb_fix_screeninfo));

    	strcpy(fix->id, "I810");
	mutex_lock(&info->mm_lock);
    	fix->smem_start = par->fb.physical;
    	fix->smem_len = par->fb.size;
	mutex_unlock(&info->mm_lock);
    	fix->type = FB_TYPE_PACKED_PIXELS;
    	fix->type_aux = 0;
	fix->xpanstep = 8;
	fix->ypanstep = 1;

    	switch (info->var.bits_per_pixel) {
	case 8:
	    	fix->visual = FB_VISUAL_PSEUDOCOLOR;
	    	break;
	case 16:
	case 24:
	case 32:
		if (info->var.nonstd)
			fix->visual = FB_VISUAL_DIRECTCOLOR;
		else
			fix->visual = FB_VISUAL_TRUECOLOR;
	    	break;
	default:
		return -EINVAL;
	}
    	fix->ywrapstep = 0;
	fix->line_length = par->pitch;
	fix->mmio_start = par->mmio_start_phys;
	fix->mmio_len = MMIO_SIZE;
	fix->accel = FB_ACCEL_I810;

	return 0;
}