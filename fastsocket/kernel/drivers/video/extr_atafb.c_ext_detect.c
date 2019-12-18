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
struct fb_var_screeninfo {int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  xres; } ;
struct atafb_par {int dummy; } ;

/* Variables and functions */
 struct fb_var_screeninfo* atafb_predefined ; 
 int /*<<< orphan*/  ext_encode_var (struct fb_var_screeninfo*,struct atafb_par*) ; 
 int /*<<< orphan*/  external_depth ; 
 int /*<<< orphan*/  external_xres ; 
 int /*<<< orphan*/  external_xres_virtual ; 
 int /*<<< orphan*/  external_yres ; 

__attribute__((used)) static int ext_detect(void)
{
	struct fb_var_screeninfo *myvar = &atafb_predefined[0];
	struct atafb_par dummy_par;

	myvar->xres = external_xres;
	myvar->xres_virtual = external_xres_virtual;
	myvar->yres = external_yres;
	myvar->bits_per_pixel = external_depth;
	ext_encode_var(myvar, &dummy_par);
	return 1;
}