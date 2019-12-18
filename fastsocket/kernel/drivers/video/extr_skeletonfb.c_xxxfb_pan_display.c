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
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int xxxfb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
    /*
     * If your hardware does not support panning, _do_ _not_ implement this
     * function. Creating a dummy function will just confuse user apps.
     */

    /*
     * Note that even if this function is fully functional, a setting of
     * 0 in both xpanstep and ypanstep means that this function will never
     * get called.
     */

    /* ... */
    return 0;
}