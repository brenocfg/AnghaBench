#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  video_font_size; } ;
struct TYPE_5__ {scalar_t__* path_font; } ;
struct TYPE_7__ {TYPE_2__ floats; TYPE_1__ paths; } ;
typedef  TYPE_3__ settings_t ;
typedef  enum font_driver_render_api { ____Placeholder_font_driver_render_api } font_driver_render_api ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 TYPE_3__* config_get_ptr () ; 
 scalar_t__ font_driver_init_first (void*,scalar_t__*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ video_font_driver ; 

void font_driver_init_osd(
      void *video_data,
      bool threading_hint,
      bool is_threaded,
      enum font_driver_render_api api)
{
   settings_t *settings = config_get_ptr();
   if (video_font_driver)
      return;

   video_font_driver = font_driver_init_first(video_data,
         *settings->paths.path_font ? settings->paths.path_font : NULL,
         settings->floats.video_font_size, threading_hint, is_threaded, api);

   if (!video_font_driver)
      RARCH_ERR("[font]: Failed to initialize OSD font.\n");
}