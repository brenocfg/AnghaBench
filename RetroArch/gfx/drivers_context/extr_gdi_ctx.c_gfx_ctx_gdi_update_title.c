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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_title ) (int /*<<< orphan*/ *,char*) ;} ;
typedef  TYPE_1__ ui_window_t ;
typedef  int /*<<< orphan*/  title ;

/* Variables and functions */
 int /*<<< orphan*/  main_window ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* ui_companion_driver_get_window_ptr () ; 
 int /*<<< orphan*/  video_driver_get_window_title (char*,int) ; 

__attribute__((used)) static void gfx_ctx_gdi_update_title(void *data, void *data2)
{
   video_frame_info_t* video_info = (video_frame_info_t*)data2;
   const ui_window_t *window      = ui_companion_driver_get_window_ptr();
   char title[128];

   title[0] = '\0';

   video_driver_get_window_title(title, sizeof(title));

   if (window && title[0])
      window->set_title(&main_window, title);
}