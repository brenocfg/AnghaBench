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

/* Variables and functions */

__attribute__((used)) static void set_line_smooth_fade_parameters(
      bool scroll_up, size_t scroll_ticks, size_t line_phase, size_t line_height,
      size_t num_lines, size_t num_display_lines, size_t line_offset, float y_offset,
      size_t *top_fade_line_offset, float *top_fade_y_offset, float *top_fade_alpha,
      size_t *bottom_fade_line_offset, float *bottom_fade_y_offset, float *bottom_fade_alpha)
{
   float fade_out_alpha     = 0.0f;
   float fade_in_alpha      = 0.0f;

   /* When a line fades out, alpha transitions from
    * 1 to 0 over the course of one half of the
    * scrolling line height. When a line fades in,
    * it's the other way around */
   fade_out_alpha           = ((float)scroll_ticks - ((float)line_phase * 2.0f)) / (float)scroll_ticks;
   fade_in_alpha            = -1.0f * fade_out_alpha;
   fade_out_alpha           = (fade_out_alpha < 0.0f) ? 0.0f : fade_out_alpha;
   fade_in_alpha            = (fade_in_alpha < 0.0f)  ? 0.0f : fade_in_alpha;

   *top_fade_line_offset    = (line_offset > 0) ? line_offset - 1 : num_lines;
   *top_fade_y_offset       = y_offset - (float)line_height;
   *top_fade_alpha          = scroll_up ? fade_out_alpha : fade_in_alpha;

   *bottom_fade_line_offset = line_offset + num_display_lines;
   *bottom_fade_y_offset    = y_offset + (float)(line_height * num_display_lines);
   *bottom_fade_alpha       = scroll_up ? fade_in_alpha : fade_out_alpha;
}