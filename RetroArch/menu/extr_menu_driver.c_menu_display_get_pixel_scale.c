#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float menu_scale_factor; } ;
struct TYPE_5__ {TYPE_1__ floats; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int DIAGONAL_PIXELS_1080P ; 
 TYPE_2__* config_get_ptr () ; 
 int sqrt (double) ; 

float menu_display_get_pixel_scale(unsigned width, unsigned height)
{
   static unsigned last_width  = 0;
   static unsigned last_height = 0;
   static float scale          = 0.0f;
   static bool scale_cached    = false;
   settings_t *settings        = config_get_ptr();

   /* We need to perform a square root here, which
    * can be slow on some platforms (not *slow*, but
    * it involves enough work that it's worth trying
    * to optimise). We therefore cache the pixel scale,
    * and only update on first run or when the video
    * size changes */
   if (!scale_cached ||
       (width  != last_width) ||
       (height != last_height))
   {
      /* Baseline reference is a 1080p display */
      scale = (float)(
            sqrt((double)((width * width) + (height * height))) /
            DIAGONAL_PIXELS_1080P);

      scale_cached = true;
      last_width   = width;
      last_height  = height;
   }

   /* Apply user scaling factor */
   if (settings)
      return scale * ((settings->floats.menu_scale_factor > 0.0001f) ?
            settings->floats.menu_scale_factor : 1.0f);

   return scale;
}