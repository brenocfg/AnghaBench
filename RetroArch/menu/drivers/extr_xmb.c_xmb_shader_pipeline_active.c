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
struct TYPE_3__ {scalar_t__ menu_shader_pipeline; } ;
typedef  TYPE_1__ video_frame_info_t ;

/* Variables and functions */
 scalar_t__ XMB_SHADER_PIPELINE_WALLPAPER ; 
 int /*<<< orphan*/  menu_driver_ident () ; 
 scalar_t__ string_is_not_equal (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool xmb_shader_pipeline_active(video_frame_info_t *video_info)
{
   if (string_is_not_equal(menu_driver_ident(), "xmb"))
      return false;
   if (video_info->menu_shader_pipeline == XMB_SHADER_PIPELINE_WALLPAPER)
      return false;
   return true;
}