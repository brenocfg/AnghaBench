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
struct fb_info {struct fb_var_screeninfo var; } ;
struct aafb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aafb_encode_var (struct fb_var_screeninfo*,struct aafb_par*) ; 
 int /*<<< orphan*/  aafb_get_par (struct aafb_par*) ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aafb_get_var(struct fb_var_screeninfo *var, int con,
			struct fb_info *info)
{
	if (con < 0) {
		struct aafb_par par;

		memset(var, 0, sizeof(struct fb_var_screeninfo));
		aafb_get_par(&par);
		aafb_encode_var(var, &par);
	} else
		*var = info->var;

	return 0;
}