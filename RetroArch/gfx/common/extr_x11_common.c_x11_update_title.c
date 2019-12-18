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
typedef  int /*<<< orphan*/  title ;

/* Variables and functions */
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  XA_STRING ; 
 int /*<<< orphan*/  XA_WM_NAME ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 int /*<<< orphan*/  g_x11_win ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  video_driver_get_window_title (char*,int) ; 

void x11_update_title(void *data, void *data2)
{
   video_frame_info_t *video_info = (video_frame_info_t*)data2;
   char title[128];

   title[0] = '\0';

   video_driver_get_window_title(title, sizeof(title));

   if (title[0])
      XChangeProperty(g_x11_dpy, g_x11_win, XA_WM_NAME, XA_STRING,
            8, PropModeReplace, (const unsigned char*)title,
            strlen(title));
}