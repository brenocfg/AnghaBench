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

__attribute__((used)) static void menu_animation_line_ticker_smooth_loop(uint64_t idx,
      bool fade_enabled, size_t line_len, size_t line_height,
      size_t max_display_lines, size_t num_lines,
      size_t *num_display_lines, size_t *line_offset, float *y_offset,
      bool *fade_active,
      size_t *top_fade_line_offset, float *top_fade_y_offset, float *top_fade_alpha,
      size_t *bottom_fade_line_offset, float *bottom_fade_y_offset, float *bottom_fade_alpha)
{
   size_t scroll_ticks  = get_line_smooth_scroll_ticks(line_len);
   size_t ticker_period = (num_lines + 1) * scroll_ticks;
   size_t phase         = idx % ticker_period;
   size_t line_phase    = phase % scroll_ticks;

   *line_offset         = phase / scroll_ticks;

   if (line_phase == (scroll_ticks - 1))
   {
      /* Static display of max_display_lines
       * (no animation) */
      *num_display_lines = max_display_lines;
      *fade_active       = false;
   }
   else
   {
      *num_display_lines = max_display_lines - 1;
      *fade_active       = fade_enabled;
   }

   *y_offset             = (float)line_height * (float)(scroll_ticks - line_phase) / (float)scroll_ticks;

   /* Set fade parameters */
   if (*fade_active)
      set_line_smooth_fade_parameters(
            true, scroll_ticks, line_phase, line_height,
            num_lines, *num_display_lines, *line_offset, *y_offset,
            top_fade_line_offset, top_fade_y_offset, top_fade_alpha,
            bottom_fade_line_offset, bottom_fade_y_offset, bottom_fade_alpha);
   else
      set_line_smooth_fade_parameters_default(
            top_fade_line_offset, top_fade_y_offset, top_fade_alpha,
            bottom_fade_line_offset, bottom_fade_y_offset, bottom_fade_alpha);
}