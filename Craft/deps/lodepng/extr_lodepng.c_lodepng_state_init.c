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
struct TYPE_3__ {int error; int /*<<< orphan*/  info_png; int /*<<< orphan*/  info_raw; int /*<<< orphan*/  encoder; int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ LodePNGState ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_color_mode_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lodepng_decoder_settings_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lodepng_encoder_settings_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lodepng_info_init (int /*<<< orphan*/ *) ; 

void lodepng_state_init(LodePNGState* state)
{
#ifdef LODEPNG_COMPILE_DECODER
  lodepng_decoder_settings_init(&state->decoder);
#endif /*LODEPNG_COMPILE_DECODER*/
#ifdef LODEPNG_COMPILE_ENCODER
  lodepng_encoder_settings_init(&state->encoder);
#endif /*LODEPNG_COMPILE_ENCODER*/
  lodepng_color_mode_init(&state->info_raw);
  lodepng_info_init(&state->info_png);
  state->error = 1;
}