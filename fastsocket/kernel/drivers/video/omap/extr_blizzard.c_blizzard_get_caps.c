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
struct omapfb_caps {int ctrl; int wnd_color; } ;
struct TYPE_4__ {scalar_t__ te_connected; TYPE_1__* int_ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_caps ) (int,struct omapfb_caps*) ;} ;

/* Variables and functions */
 int OMAPFB_CAPS_MANUAL_UPDATE ; 
 int OMAPFB_CAPS_TEARSYNC ; 
 int OMAPFB_CAPS_WINDOW_OVERLAY ; 
 int OMAPFB_CAPS_WINDOW_PIXEL_DOUBLE ; 
 int OMAPFB_CAPS_WINDOW_ROTATE ; 
 int OMAPFB_CAPS_WINDOW_SCALE ; 
 int OMAPFB_COLOR_RGB565 ; 
 int OMAPFB_COLOR_YUV420 ; 
 TYPE_2__ blizzard ; 
 int /*<<< orphan*/  stub1 (int,struct omapfb_caps*) ; 

__attribute__((used)) static void blizzard_get_caps(int plane, struct omapfb_caps *caps)
{
	blizzard.int_ctrl->get_caps(plane, caps);
	caps->ctrl |= OMAPFB_CAPS_MANUAL_UPDATE |
		OMAPFB_CAPS_WINDOW_PIXEL_DOUBLE |
		OMAPFB_CAPS_WINDOW_SCALE |
		OMAPFB_CAPS_WINDOW_OVERLAY |
		OMAPFB_CAPS_WINDOW_ROTATE;
	if (blizzard.te_connected)
		caps->ctrl |= OMAPFB_CAPS_TEARSYNC;
	caps->wnd_color |= (1 << OMAPFB_COLOR_RGB565) |
			   (1 << OMAPFB_COLOR_YUV420);
}