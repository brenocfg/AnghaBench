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
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  XF86VidModeModeInfo ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XF86VidModeSetViewPort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XF86VidModeSwitchToMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desktop_mode ; 
 int /*<<< orphan*/  get_video_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool x11_enter_fullscreen(video_frame_info_t *video_info,
      Display *dpy, unsigned width,
      unsigned height)
{
   XF86VidModeModeInfo mode;

   if (!get_video_mode(video_info, dpy, width, height, &mode, &desktop_mode))
      return false;

   if (!XF86VidModeSwitchToMode(dpy, DefaultScreen(dpy), &mode))
      return false;

   XF86VidModeSetViewPort(dpy, DefaultScreen(dpy), 0, 0);
   return true;
}