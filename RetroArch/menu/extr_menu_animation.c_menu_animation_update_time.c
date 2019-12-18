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
struct TYPE_6__ {int /*<<< orphan*/  menu_driver; } ;
struct TYPE_5__ {float menu_ticker_speed; } ;
struct TYPE_7__ {TYPE_2__ arrays; TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;
typedef  scalar_t__ retro_time_t ;

/* Variables and functions */
 scalar_t__ TICKER_SLOW_SPEED ; 
 scalar_t__ TICKER_SPEED ; 
 int animation_is_active ; 
 TYPE_3__* config_get_ptr () ; 
 scalar_t__ cpu_features_get_time_usec () ; 
 scalar_t__ cur_time ; 
 float delta_time ; 
 float menu_display_get_dpi_scale (unsigned int,unsigned int) ; 
 scalar_t__ old_time ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ticker_idx ; 
 scalar_t__ ticker_is_active ; 
 unsigned int ticker_pixel_idx ; 
 float ticker_pixel_period ; 
 int /*<<< orphan*/  ticker_slow_idx ; 

__attribute__((used)) static void menu_animation_update_time(bool timedate_enable, unsigned video_width, unsigned video_height)
{
   static retro_time_t
      last_clock_update       = 0;
   static retro_time_t
      last_ticker_update      = 0;
   static retro_time_t
      last_ticker_slow_update = 0;

   static float ticker_pixel_accumulator  = 0.0f;
   unsigned ticker_pixel_accumulator_uint = 0;
   float ticker_pixel_increment           = 0.0f;

   /* Adjust ticker speed */
   settings_t *settings       = config_get_ptr();
   float speed_factor         = settings->floats.menu_ticker_speed > 0.0001f ? settings->floats.menu_ticker_speed : 1.0f;
   unsigned ticker_speed      = (unsigned)(((float)TICKER_SPEED / speed_factor) + 0.5);
   unsigned ticker_slow_speed = (unsigned)(((float)TICKER_SLOW_SPEED / speed_factor) + 0.5);

   /* Note: cur_time & old_time are in us, delta_time is in ms */
   cur_time   = cpu_features_get_time_usec();
   delta_time = old_time == 0 ? 0.0f : (float)(cur_time - old_time) / 1000.0f;
   old_time   = cur_time;

   if (((cur_time - last_clock_update) > 1000000) /* 1000000 us == 1 second */
         && timedate_enable)
   {
      animation_is_active   = true;
      last_clock_update     = cur_time;
   }

   if (ticker_is_active)
   {
      if (cur_time - last_ticker_update >= ticker_speed)
      {
         ticker_idx++;
         last_ticker_update = cur_time;
      }

      if (cur_time - last_ticker_slow_update >= ticker_slow_speed)
      {
         ticker_slow_idx++;
         last_ticker_slow_update = cur_time;
      }

      /* Pixel ticker updates every frame (regardless of time delta),
       * so requires special handling */

      /* > Get base increment size (+1 every ticker_pixel_period ms) */
      ticker_pixel_increment = delta_time / ticker_pixel_period;

      /* > Apply ticker speed adjustment */
      ticker_pixel_increment *= speed_factor;

      /* > Apply display resolution adjustment
       *   (baseline resolution: 1920x1080)
       *   Note 1: RGUI framebuffer size is independent of
       *   display resolution, so have to use a fixed multiplier.
       *   We choose a value such that text is scrolled
       *   1 pixel every 4 frames when ticker speed is 1x,
       *   which matches almost exactly the scroll speed
       *   of non-smooth ticker text (scrolling 1 pixel
       *   every 2 frames is optimal, but may be too fast
       *   for some users - so play it safe. Users can always
       *   set ticker speed to 2x if they prefer)
       *   Note 2: It turns out that resolution adjustment
       *   also fails for Ozone, because it doesn't implement
       *   any kind of DPI scaling - i.e. text gets smaller
       *   as resolution increases. This is annoying. It
       *   means we have to use a fixed multiplier for
       *   Ozone as well...
       *   Note 3: GLUI uses the new DPI scaling system,
       *   so scaling multiplier is menu_display_get_dpi_scale()
       *   multiplied by a small correction factor (since the
       *   default 1.0x speed is just a little faster than the
       *   non-smooth ticker) */
      if (string_is_equal(settings->arrays.menu_driver, "rgui"))
         ticker_pixel_increment *= 0.25f;
      /* TODO/FIXME: Remove this Ozone special case if/when
       * Ozone gets proper DPI scaling */
      else if (string_is_equal(settings->arrays.menu_driver, "ozone"))
         ticker_pixel_increment *= 0.5f;
      else if (string_is_equal(settings->arrays.menu_driver, "glui"))
         ticker_pixel_increment *= (menu_display_get_dpi_scale(video_width, video_height) * 0.8f);
      else if (video_width > 0)
         ticker_pixel_increment *= ((float)video_width / 1920.0f);

      /* > Update accumulator */
      ticker_pixel_accumulator += ticker_pixel_increment;
      ticker_pixel_accumulator_uint = (unsigned)ticker_pixel_accumulator;

      /* > Check whether we've accumulated enough for an idx update */
      if (ticker_pixel_accumulator_uint > 0)
      {
         ticker_pixel_idx += ticker_pixel_accumulator_uint;
         ticker_pixel_accumulator -= (float)ticker_pixel_accumulator_uint;
      }
   }
}