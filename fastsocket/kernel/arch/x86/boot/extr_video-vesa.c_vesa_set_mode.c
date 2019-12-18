#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct mode_info {int mode; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct biosregs {int ax; int cx; size_t di; int bx; } ;
struct TYPE_3__ {int mode_attr; } ;

/* Variables and functions */
 int VIDEO_FIRST_VESA ; 
 int do_restore ; 
 int /*<<< orphan*/  force_x ; 
 int /*<<< orphan*/  force_y ; 
 int graphic_mode ; 
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,struct biosregs*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vesa_store_mode_params_graphics () ; 
 TYPE_1__ vminfo ; 

__attribute__((used)) static int vesa_set_mode(struct mode_info *mode)
{
	struct biosregs ireg, oreg;
	int is_graphic;
	u16 vesa_mode = mode->mode - VIDEO_FIRST_VESA;

	memset(&vminfo, 0, sizeof vminfo); /* Just in case... */

	initregs(&ireg);
	ireg.ax = 0x4f01;
	ireg.cx = vesa_mode;
	ireg.di = (size_t)&vminfo;
	intcall(0x10, &ireg, &oreg);

	if (oreg.ax != 0x004f)
		return -1;

	if ((vminfo.mode_attr & 0x15) == 0x05) {
		/* It's a supported text mode */
		is_graphic = 0;
#ifdef CONFIG_FB_BOOT_VESA_SUPPORT
	} else if ((vminfo.mode_attr & 0x99) == 0x99) {
		/* It's a graphics mode with linear frame buffer */
		is_graphic = 1;
		vesa_mode |= 0x4000; /* Request linear frame buffer */
#endif
	} else {
		return -1;	/* Invalid mode */
	}


	initregs(&ireg);
	ireg.ax = 0x4f02;
	ireg.bx = vesa_mode;
	intcall(0x10, &ireg, &oreg);

	if (oreg.ax != 0x004f)
		return -1;

	graphic_mode = is_graphic;
	if (!is_graphic) {
		/* Text mode */
		force_x = mode->x;
		force_y = mode->y;
		do_restore = 1;
	} else {
		/* Graphics mode */
		vesa_store_mode_params_graphics();
	}

	return 0;
}