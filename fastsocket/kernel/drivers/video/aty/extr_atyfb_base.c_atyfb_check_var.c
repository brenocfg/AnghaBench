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
typedef  union aty_pll {int dummy; } aty_pll ;
typedef  scalar_t__ u32 ;
struct fb_var_screeninfo {int activate; int accel_flags; int /*<<< orphan*/  pixclock; int /*<<< orphan*/  bits_per_pixel; } ;
struct TYPE_3__ {int accel_flags; } ;
struct fb_info {TYPE_1__ var; scalar_t__ par; } ;
struct crtc {int dummy; } ;
struct atyfb_par {TYPE_2__* pll_ops; int /*<<< orphan*/  pll; } ;
typedef  int /*<<< orphan*/  pll ;
struct TYPE_4__ {int (* var_to_pll ) (struct fb_info*,scalar_t__,int /*<<< orphan*/ ,union aty_pll*) ;int /*<<< orphan*/  (* pll_to_var ) (struct fb_info*,union aty_pll*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int FB_ACCELF_TEXT ; 
 int FB_ACTIVATE_TEST ; 
 int /*<<< orphan*/  PRINTKE (char*) ; 
 int /*<<< orphan*/  aty_crtc_to_var (struct crtc*,struct fb_var_screeninfo*) ; 
 int aty_var_to_crtc (struct fb_info*,struct fb_var_screeninfo*,struct crtc*) ; 
 scalar_t__ atyfb_get_pixclock (struct fb_var_screeninfo*,struct atyfb_par*) ; 
 int /*<<< orphan*/  memcpy (union aty_pll*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct fb_info*,scalar_t__,int /*<<< orphan*/ ,union aty_pll*) ; 
 int /*<<< orphan*/  stub2 (struct fb_info*,union aty_pll*) ; 

__attribute__((used)) static int atyfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	int err;
	struct crtc crtc;
	union aty_pll pll;
	u32 pixclock;

	memcpy(&pll, &par->pll, sizeof(pll));

	err = aty_var_to_crtc(info, var, &crtc);
	if (err)
		return err;

	pixclock = atyfb_get_pixclock(var, par);

	if (pixclock == 0) {
		if (!(var->activate & FB_ACTIVATE_TEST))
			PRINTKE("Invalid pixclock\n");
		return -EINVAL;
	} else {
		err = par->pll_ops->var_to_pll(info, pixclock,
					       var->bits_per_pixel, &pll);
		if (err)
			return err;
	}

	if (var->accel_flags & FB_ACCELF_TEXT)
		info->var.accel_flags = FB_ACCELF_TEXT;
	else
		info->var.accel_flags = 0;

	aty_crtc_to_var(&crtc, var);
	var->pixclock = par->pll_ops->pll_to_var(info, &pll);
	return 0;
}