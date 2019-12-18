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
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int dummy; } ;
struct atafb_par {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* encode_var ) (struct fb_var_screeninfo*,struct atafb_par*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ata_get_par (struct atafb_par*) ; 
 TYPE_1__* fbhw ; 
 int /*<<< orphan*/  stub1 (struct fb_var_screeninfo*,struct atafb_par*) ; 

__attribute__((used)) static int atafb_get_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct atafb_par par;

	ata_get_par(&par);
	fbhw->encode_var(var, &par);

	return 0;
}