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

__attribute__((used)) static void set_line_smooth_fade_parameters_default(
      size_t *top_fade_line_offset, float *top_fade_y_offset, float *top_fade_alpha,
      size_t *bottom_fade_line_offset, float *bottom_fade_y_offset, float *bottom_fade_alpha)
{
   *top_fade_line_offset    = 0;
   *top_fade_y_offset       = 0.0f;
   *top_fade_alpha          = 0.0f;

   *bottom_fade_line_offset = 0;
   *bottom_fade_y_offset    = 0.0f;
   *bottom_fade_alpha       = 0.0f;
}