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
 size_t get_line_display_ticks (size_t) ; 

__attribute__((used)) static void menu_animation_line_ticker_generic(uint64_t idx,
      size_t line_len, size_t max_lines, size_t num_lines,
      size_t *line_offset)
{
   size_t line_ticks    = get_line_display_ticks(line_len);
   /* Note: This function is only called if num_lines > max_lines */
   size_t excess_lines  = num_lines - max_lines;
   /* Ticker will pause for one line duration when the first
    * or last line is reached (this is mostly required for the
    * case where num_lines == (max_lines + 1), since otherwise
    * the text flicks rapidly up and down in disconcerting
    * fashion...) */
   size_t ticker_period = (excess_lines * 2) + 2;
   size_t phase         = (idx / line_ticks) % ticker_period;

   /* Pause on first line */
   if (phase > 0)
      phase--;
   /* Pause on last line */
   if (phase > excess_lines)
      phase--;

   /* Lines scrolling upwards */
   if (phase <= excess_lines)
      *line_offset = phase;
   /* Lines scrolling downwards */
   else
      *line_offset = (excess_lines * 2) - phase;
}