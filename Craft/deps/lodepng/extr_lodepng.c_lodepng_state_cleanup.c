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
struct TYPE_3__ {int /*<<< orphan*/  info_png; int /*<<< orphan*/  info_raw; } ;
typedef  TYPE_1__ LodePNGState ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_color_mode_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lodepng_info_cleanup (int /*<<< orphan*/ *) ; 

void lodepng_state_cleanup(LodePNGState* state)
{
  lodepng_color_mode_cleanup(&state->info_raw);
  lodepng_info_cleanup(&state->info_png);
}