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
 float ticker_pixel_period ; 

__attribute__((used)) static size_t get_line_smooth_scroll_ticks(size_t line_len)
{
   /* Mean human reading speed for all western languages,
    * characters per minute */
   float cpm            = 1000.0f;
   /* Base time for which a line should be shown, in ms */
   float line_duration  = (line_len * 60.0f * 1000.0f) / cpm;
   /* Ticker updates (nominally) once every ticker_pixel_period ms
    * > Return base number of ticks for which text should scroll
    *   from one line to the next */
   return (size_t)(line_duration / ticker_pixel_period);
}