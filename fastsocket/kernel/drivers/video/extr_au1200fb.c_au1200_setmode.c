#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  line_length; } ;
struct TYPE_9__ {TYPE_2__ fix; } ;
struct au1200fb_device {int plane; TYPE_3__ fb_info; } ;
struct TYPE_12__ {int /*<<< orphan*/  winenable; TYPE_1__* window; } ;
struct TYPE_11__ {TYPE_4__* w; } ;
struct TYPE_10__ {int mode_winctrl1; int /*<<< orphan*/  mode_winenable; int /*<<< orphan*/  ypos; int /*<<< orphan*/  xpos; } ;
struct TYPE_7__ {int winctrl1; int winctrl2; } ;

/* Variables and functions */
 int LCD_WINCTRL1_PRI_N (int) ; 
 int LCD_WINCTRL2_BX_N (int /*<<< orphan*/ ) ; 
 int LCD_WINCTRL2_CKMODE_00 ; 
 int LCD_WINCTRL2_DBM ; 
 int LCD_WINCTRL2_SCX_1 ; 
 int LCD_WINCTRL2_SCY_1 ; 
 int /*<<< orphan*/  au1200_setlocation (struct au1200fb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 TYPE_6__* lcd ; 
 TYPE_5__* win ; 

__attribute__((used)) static void au1200_setmode(struct au1200fb_device *fbdev)
{
	int plane = fbdev->plane;
	/* Window/plane setup */
	lcd->window[plane].winctrl1 = ( 0
		| LCD_WINCTRL1_PRI_N(plane)
		| win->w[plane].mode_winctrl1 /* FRM,CCO,PO,PIPE */
		) ;

	au1200_setlocation(fbdev, plane, win->w[plane].xpos, win->w[plane].ypos);

	lcd->window[plane].winctrl2 = ( 0
		| LCD_WINCTRL2_CKMODE_00
		| LCD_WINCTRL2_DBM
		| LCD_WINCTRL2_BX_N( fbdev->fb_info.fix.line_length)
		| LCD_WINCTRL2_SCX_1
		| LCD_WINCTRL2_SCY_1
		) ;
	lcd->winenable |= win->w[plane].mode_winenable;
	au_sync();
}