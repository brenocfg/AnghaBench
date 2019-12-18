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
typedef  int u32 ;
struct tdfx_par {int dummy; } ;
struct fb_info {struct tdfx_par* par; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DACMODE ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  banshee_make_room (struct tdfx_par*,int) ; 
 int tdfx_inl (struct tdfx_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdfx_outl (struct tdfx_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_disable_video (struct tdfx_par*) ; 
 int /*<<< orphan*/  vga_enable_video (struct tdfx_par*) ; 

__attribute__((used)) static int tdfxfb_blank(int blank, struct fb_info *info)
{
	struct tdfx_par *par = info->par;
	int vgablank = 1;
	u32 dacmode = tdfx_inl(par, DACMODE);

	dacmode &= ~(BIT(1) | BIT(3));

	switch (blank) {
	case FB_BLANK_UNBLANK: /* Screen: On; HSync: On, VSync: On */
		vgablank = 0;
		break;
	case FB_BLANK_NORMAL: /* Screen: Off; HSync: On, VSync: On */
		break;
	case FB_BLANK_VSYNC_SUSPEND: /* Screen: Off; HSync: On, VSync: Off */
		dacmode |= BIT(3);
		break;
	case FB_BLANK_HSYNC_SUSPEND: /* Screen: Off; HSync: Off, VSync: On */
		dacmode |= BIT(1);
		break;
	case FB_BLANK_POWERDOWN: /* Screen: Off; HSync: Off, VSync: Off */
		dacmode |= BIT(1) | BIT(3);
		break;
	}

	banshee_make_room(par, 1);
	tdfx_outl(par, DACMODE, dacmode);
	if (vgablank)
		vga_disable_video(par);
	else
		vga_enable_video(par);
	return 0;
}