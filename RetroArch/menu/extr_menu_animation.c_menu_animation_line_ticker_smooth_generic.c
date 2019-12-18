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
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t get_line_smooth_scroll_ticks (size_t) ; 
 int /*<<< orphan*/  set_line_smooth_fade_parameters (int,size_t,size_t,size_t,size_t,size_t,size_t,float,size_t*,float*,float*,size_t*,float*,float*) ; 
 int /*<<< orphan*/  set_line_smooth_fade_parameters_default (size_t*,float*,float*,size_t*,float*,float*) ; 

__attribute__((used)) static void menu_animation_line_ticker_smooth_generic(uint64_t idx,
      bool fade_enabled, size_t line_len, size_t line_height,
      size_t max_display_lines, size_t num_lines,
      size_t *num_display_lines, size_t *line_offset, float *y_offset,
      bool *fade_active,
      size_t *top_fade_line_offset, float *top_fade_y_offset, float *top_fade_alpha,
      size_t *bottom_fade_line_offset, float *bottom_fade_y_offset, float *bottom_fade_alpha)
{
   size_t scroll_ticks  = get_line_smooth_scroll_ticks(line_len);
   /* Note: This function is only called if num_lines > max_display_lines */
   size_t excess_lines  = num_lines - max_display_lines;
   /* Ticker will pause for one line duration when the first
    * or last line is reached */
   size_t ticker_period = ((excess_lines * 2) + 2) * scroll_ticks;
   size_t phase         = idx % ticker_period;
   size_t line_phase    = 0;
   bool pause           = false;
   bool scroll_up       = true;

   /* Pause on first line */
   if (phase < scroll_ticks)
      pause = true;
   phase = (phase >= scroll_ticks) ? phase - scroll_ticks : 0;
   /* Pause on last line and change direction */
   if (phase >= excess_lines * scroll_ticks)
   {
      scroll_up = false;

      if (phase < (excess_lines + 1) * scroll_ticks)
      {
         pause = true;
         phase = 0;
      }
      else
         phase -= (excess_lines + 1) * scroll_ticks;
   }

   line_phase = phase % scroll_ticks;

   if (pause || (line_phase == 0))
   {
      /* Static display of max_display_lines
       * (no animation) */
      *num_display_lines = max_display_lines;
      *y_offset          = 0.0f;
      *fade_active       = false;

      if (pause)
         *line_offset    = scroll_up ? 0 : excess_lines;
      else
         *line_offset    = scroll_up ? (phase / scroll_ticks) : (excess_lines - (phase / scroll_ticks));
   }
   else
   {
      /* Scroll animation is active */
      *num_display_lines = max_display_lines - 1;
      *fade_active       = fade_enabled;

      if (scroll_up)
      {
         *line_offset    = (phase / scroll_ticks) + 1;
         *y_offset       = (float)line_height * (float)(scroll_ticks - line_phase) / (float)scroll_ticks;
      }
      else
      {
         *line_offset = excess_lines - (phase / scroll_ticks);
         *y_offset    = (float)line_height * (1.0f - (float)(scroll_ticks - line_phase) / (float)scroll_ticks);
      }

      /* Set fade parameters if fade animation is active */
      if (*fade_active)
         set_line_smooth_fade_parameters(
               scroll_up, scroll_ticks, line_phase, line_height,
               num_lines, *num_display_lines, *line_offset, *y_offset,
               top_fade_line_offset, top_fade_y_offset, top_fade_alpha,
               bottom_fade_line_offset, bottom_fade_y_offset, bottom_fade_alpha);
   }

   /* Set 'default' fade parameters if fade animation
    * is inactive */
   if (!*fade_active)
      set_line_smooth_fade_parameters_default(
            top_fade_line_offset, top_fade_y_offset, top_fade_alpha,
            bottom_fade_line_offset, bottom_fade_y_offset, bottom_fade_alpha);
}