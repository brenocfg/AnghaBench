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
typedef  int /*<<< orphan*/  uint8_t ;
struct scaler_ctx {int /*<<< orphan*/  in_fmt; } ;
struct TYPE_3__ {scalar_t__ pixel_format_type; int pitch; int width; scalar_t__ height; scalar_t__ frame; int /*<<< orphan*/  filename; scalar_t__ bgr24; int /*<<< orphan*/  out_buffer; int /*<<< orphan*/  scaler; } ;
typedef  TYPE_1__ screenshot_task_state_t ;
typedef  enum rbmp_source_type { ____Placeholder_rbmp_source_type } rbmp_source_type ;

/* Variables and functions */
 int RBMP_SOURCE_TYPE_BGR24 ; 
 int RBMP_SOURCE_TYPE_DONT_CARE ; 
 int RBMP_SOURCE_TYPE_XRGB888 ; 
 scalar_t__ RETRO_PIXEL_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  SCALER_FMT_ARGB8888 ; 
 int /*<<< orphan*/  SCALER_FMT_BGR24 ; 
 int /*<<< orphan*/  SCALER_FMT_RGB565 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int rbmp_save_image (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int,int) ; 
 int rpng_save_image_bgr24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  scaler_ctx_gen_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_frame_convert_to_bgr24 (struct scaler_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__,int) ; 

__attribute__((used)) static bool screenshot_dump_direct(screenshot_task_state_t *state)
{
   struct scaler_ctx *scaler      = (struct scaler_ctx*)&state->scaler;
   bool ret                       = false;

#if defined(HAVE_RPNG)
   if (state->bgr24)
      scaler->in_fmt              = SCALER_FMT_BGR24;
   else if (state->pixel_format_type == RETRO_PIXEL_FORMAT_XRGB8888)
      scaler->in_fmt              = SCALER_FMT_ARGB8888;
   else
      scaler->in_fmt              = SCALER_FMT_RGB565;

   video_frame_convert_to_bgr24(
         scaler,
         state->out_buffer,
         (const uint8_t*)state->frame + ((int)state->height - 1)
         * state->pitch,
         state->width, state->height,
         -state->pitch);

   scaler_ctx_gen_reset(&state->scaler);

   ret = rpng_save_image_bgr24(
         state->filename,
         state->out_buffer,
         state->width,
         state->height,
         state->width * 3
         );

   free(state->out_buffer);
#elif defined(HAVE_RBMP)
   {
      enum rbmp_source_type bmp_type = RBMP_SOURCE_TYPE_DONT_CARE;
      if (state->bgr24)
         bmp_type = RBMP_SOURCE_TYPE_BGR24;
      else if (state->pixel_format_type == RETRO_PIXEL_FORMAT_XRGB8888)
         bmp_type = RBMP_SOURCE_TYPE_XRGB888;

      ret = rbmp_save_image(state->filename,
            state->frame,
            state->width,
            state->height,
            state->pitch,
            bmp_type);
   }
#endif

   return ret;
}