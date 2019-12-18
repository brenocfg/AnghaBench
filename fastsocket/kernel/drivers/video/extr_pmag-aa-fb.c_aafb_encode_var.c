#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_7__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_6__ {int length; scalar_t__ msb_right; scalar_t__ offset; } ;
struct TYPE_5__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct fb_var_screeninfo {int xres; int yres; int xres_virtual; int yres_virtual; int bits_per_pixel; int grayscale; int activate; int vmode; int /*<<< orphan*/  sync; scalar_t__ accel_flags; scalar_t__ nonstd; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct aafb_par {int dummy; } ;

/* Variables and functions */
 int FB_ACTIVATE_MASK ; 
 int FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_SYNC_ON_GREEN ; 
 int FB_VMODE_MASK ; 
 int FB_VMODE_NONINTERLACED ; 

__attribute__((used)) static void aafb_encode_var(struct fb_var_screeninfo *var,
			    struct aafb_par *par)
{
	var->xres = 1280;
	var->yres = 1024;
	var->xres_virtual = 2048;
	var->yres_virtual = 1024;
	var->xoffset = 0;
	var->yoffset = 0;
	var->bits_per_pixel = 8;
	var->grayscale = 1;
	var->red.offset = 0;
	var->red.length = 0;
	var->red.msb_right = 0;
	var->green.offset = 0;
	var->green.length = 1;
	var->green.msb_right = 0;
	var->blue.offset = 0;
	var->blue.length = 0;
	var->blue.msb_right = 0;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	var->nonstd = 0;
	var->activate &= ~FB_ACTIVATE_MASK & FB_ACTIVATE_NOW;
	var->accel_flags = 0;
	var->sync = FB_SYNC_ON_GREEN;
	var->vmode &= ~FB_VMODE_MASK & FB_VMODE_NONINTERLACED;
}