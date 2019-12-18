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

/* Variables and functions */
 int /*<<< orphan*/  Supexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * coltable ; 
 int /*<<< orphan*/ * coltable_backup ; 
 int /*<<< orphan*/  f030_coltable_ptr ; 
 int /*<<< orphan*/  f030coltable ; 
 int /*<<< orphan*/  f030coltable_backup ; 
 int /*<<< orphan*/  gl_vdi_handle ; 
 scalar_t__ reprogram_VIDEL ; 
 int /*<<< orphan*/  set_colors_on_f030 ; 
 int /*<<< orphan*/  vs_color (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void set_colors(int new)
{
	int i;

	if (reprogram_VIDEL) {
		if (new)
			f030_coltable_ptr = f030coltable;
		else
			f030_coltable_ptr = f030coltable_backup;
		Supexec(set_colors_on_f030);
		/* VsetRGB(0, 256, new ? RGBcoltable : RGBcoltable_backup); */
	}
	else {
		for(i=0; i<256; i++)
			vs_color(gl_vdi_handle, i, new ? coltable[i] : coltable_backup[i]);
	}
}