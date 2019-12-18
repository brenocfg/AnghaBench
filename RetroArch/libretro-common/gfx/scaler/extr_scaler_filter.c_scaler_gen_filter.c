#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int filter_len; int filter_stride; int* filter_pos; int /*<<< orphan*/ * filter; } ;
struct scaler_ctx {int scaler_type; int in_width; int out_width; int out_height; int in_height; TYPE_1__ vert; TYPE_1__ horiz; int /*<<< orphan*/  scaler_special; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  SCALER_TYPE_BILINEAR 131 
#define  SCALER_TYPE_POINT 130 
#define  SCALER_TYPE_SINC 129 
#define  SCALER_TYPE_UNKNOWN 128 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fixup_filter_sub (TYPE_1__*,int,double) ; 
 int /*<<< orphan*/  gen_filter_bilinear_sub (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  gen_filter_point_sub (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  gen_filter_sinc_sub (TYPE_1__*,int,int,int,double) ; 
 int next_pow2 (int) ; 
 int /*<<< orphan*/  scaler_argb8888_point_special ; 
 int validate_filter (struct scaler_ctx*) ; 

bool scaler_gen_filter(struct scaler_ctx *ctx)
{
   int x_pos, x_step, y_pos, y_step;
   int sinc_size = 0;

   switch (ctx->scaler_type)
   {
      case SCALER_TYPE_POINT:
         ctx->horiz.filter_len    = 1;
         ctx->horiz.filter_stride = 1;
         ctx->vert.filter_len     = 1;
         ctx->vert.filter_stride  = 1;
         break;
      case SCALER_TYPE_BILINEAR:
         ctx->horiz.filter_len    = 2;
         ctx->horiz.filter_stride = 2;
         ctx->vert.filter_len     = 2;
         ctx->vert.filter_stride  = 2;
         break;
      case SCALER_TYPE_SINC:
         sinc_size                = 8 * ((ctx->in_width > ctx->out_width)
               ? next_pow2(ctx->in_width / ctx->out_width) : 1);
         ctx->horiz.filter_len    = sinc_size;
         ctx->horiz.filter_stride = sinc_size;
         ctx->vert.filter_len     = sinc_size;
         ctx->vert.filter_stride  = sinc_size;
         break;
      case SCALER_TYPE_UNKNOWN:
      default:
         return false;
   }

   ctx->horiz.filter     = (int16_t*)calloc(sizeof(int16_t), ctx->horiz.filter_stride * ctx->out_width);
   ctx->horiz.filter_pos = (int*)calloc(sizeof(int), ctx->out_width);

   ctx->vert.filter      = (int16_t*)calloc(sizeof(int16_t), ctx->vert.filter_stride * ctx->out_height);
   ctx->vert.filter_pos  = (int*)calloc(sizeof(int), ctx->out_height);

   if (!ctx->horiz.filter || !ctx->vert.filter)
      return false;

   x_step = (1 << 16) * ctx->in_width / ctx->out_width;
   y_step = (1 << 16) * ctx->in_height / ctx->out_height;

   switch (ctx->scaler_type)
   {
      case SCALER_TYPE_POINT:
         x_pos  = (1 << 15) * ctx->in_width / ctx->out_width   - (1 << 15);
         y_pos  = (1 << 15) * ctx->in_height / ctx->out_height - (1 << 15);

         gen_filter_point_sub(&ctx->horiz, ctx->out_width,  x_pos, x_step);
         gen_filter_point_sub(&ctx->vert,  ctx->out_height, y_pos, y_step);

         ctx->scaler_special = scaler_argb8888_point_special;
         break;

      case SCALER_TYPE_BILINEAR:
         x_pos  = (1 << 15) * ctx->in_width / ctx->out_width   - (1 << 15);
         y_pos  = (1 << 15) * ctx->in_height / ctx->out_height - (1 << 15);

         gen_filter_bilinear_sub(&ctx->horiz, ctx->out_width,  x_pos, x_step);
         gen_filter_bilinear_sub(&ctx->vert,  ctx->out_height, y_pos, y_step);
         break;

      case SCALER_TYPE_SINC:
         /* Need to expand the filter when downsampling
          * to get a proper low-pass effect. */

         x_pos  = (1 << 15) * ctx->in_width  / ctx->out_width  - (1 << 15) - (sinc_size << 15);
         y_pos  = (1 << 15) * ctx->in_height / ctx->out_height - (1 << 15) - (sinc_size << 15);

         gen_filter_sinc_sub(&ctx->horiz, ctx->out_width, x_pos, x_step,
               ctx->in_width  > ctx->out_width  ? (double)ctx->out_width  / ctx->in_width  : 1.0);
         gen_filter_sinc_sub(&ctx->vert, ctx->out_height, y_pos, y_step,
               ctx->in_height > ctx->out_height ? (double)ctx->out_height / ctx->in_height : 1.0
               );
         break;
      case SCALER_TYPE_UNKNOWN:
         break;
   }

   /* Makes sure that we never sample outside our rectangle. */
   fixup_filter_sub(&ctx->horiz, ctx->out_width, ctx->in_width);
   fixup_filter_sub(&ctx->vert,  ctx->out_height, ctx->in_height);

   return validate_filter(ctx);
}