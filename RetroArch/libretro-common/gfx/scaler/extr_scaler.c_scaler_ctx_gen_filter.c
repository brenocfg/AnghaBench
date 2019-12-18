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
struct scaler_ctx {int unscaled; scalar_t__ in_width; scalar_t__ out_width; scalar_t__ in_height; scalar_t__ out_height; int in_fmt; int out_fmt; void* out_pixconv; void* in_pixconv; int /*<<< orphan*/  scaler_vert; int /*<<< orphan*/  scaler_horiz; void* direct_pixconv; int /*<<< orphan*/ * scaler_special; } ;

/* Variables and functions */
#define  SCALER_FMT_0RGB1555 134 
#define  SCALER_FMT_ABGR8888 133 
#define  SCALER_FMT_ARGB8888 132 
#define  SCALER_FMT_BGR24 131 
#define  SCALER_FMT_RGB565 130 
#define  SCALER_FMT_RGBA4444 129 
#define  SCALER_FMT_YUYV 128 
 int /*<<< orphan*/  allocate_frames (struct scaler_ctx*) ; 
 void* conv_0rgb1555_argb8888 ; 
 void* conv_0rgb1555_bgr24 ; 
 void* conv_0rgb1555_rgb565 ; 
 void* conv_abgr8888_bgr24 ; 
 void* conv_argb8888_0rgb1555 ; 
 void* conv_argb8888_abgr8888 ; 
 void* conv_argb8888_bgr24 ; 
 void* conv_argb8888_rgba4444 ; 
 void* conv_bgr24_argb8888 ; 
 void* conv_bgr24_rgb565 ; 
 void* conv_copy ; 
 void* conv_rgb565_0rgb1555 ; 
 void* conv_rgb565_abgr8888 ; 
 void* conv_rgb565_argb8888 ; 
 void* conv_rgb565_bgr24 ; 
 void* conv_rgba4444_argb8888 ; 
 void* conv_rgba4444_rgb565 ; 
 void* conv_yuyv_argb8888 ; 
 int /*<<< orphan*/  scaler_argb8888_horiz ; 
 int /*<<< orphan*/  scaler_argb8888_vert ; 
 int /*<<< orphan*/  scaler_ctx_gen_reset (struct scaler_ctx*) ; 
 int /*<<< orphan*/  scaler_gen_filter (struct scaler_ctx*) ; 

bool scaler_ctx_gen_filter(struct scaler_ctx *ctx)
{
   scaler_ctx_gen_reset(ctx);

   ctx->scaler_special = NULL;
   ctx->unscaled       = false;

   if (!allocate_frames(ctx))
      return false;

   if (     ctx->in_width  == ctx->out_width
         && ctx->in_height == ctx->out_height)
   {
      ctx->unscaled     = true; /* Only pixel format conversion ... */

      if (ctx->in_fmt == ctx->out_fmt)
         ctx->direct_pixconv = conv_copy;
      else
      {
         /* Bind a pixel converter callback function to the
          * 'direct_pixconv' function pointer of the scaler context object. */
         switch (ctx->in_fmt)
         {
            case SCALER_FMT_0RGB1555:
               switch (ctx->out_fmt)
               {
                  case SCALER_FMT_ARGB8888:
                     ctx->direct_pixconv = conv_0rgb1555_argb8888;
                     break;
                  case SCALER_FMT_RGB565:
                     ctx->direct_pixconv = conv_0rgb1555_rgb565;
                     break;
                  case SCALER_FMT_BGR24:
                     ctx->direct_pixconv = conv_0rgb1555_bgr24;
                     break;
                  default:
                     break;
               }
               break;
            case SCALER_FMT_RGB565:
               switch (ctx->out_fmt)
               {
                  case SCALER_FMT_ARGB8888:
                     ctx->direct_pixconv = conv_rgb565_argb8888;
                     break;
                  case SCALER_FMT_ABGR8888:
                     ctx->direct_pixconv = conv_rgb565_abgr8888;
                     break;
                  case SCALER_FMT_BGR24:
                     ctx->direct_pixconv = conv_rgb565_bgr24;
                     break;
                  case SCALER_FMT_0RGB1555:
                     ctx->direct_pixconv = conv_rgb565_0rgb1555;
                     break;
                  default:
                     break;
               }
               break;
            case SCALER_FMT_BGR24:
               switch (ctx->out_fmt)
               {
                  case SCALER_FMT_ARGB8888:
                     ctx->direct_pixconv = conv_bgr24_argb8888;
                     break;
                  case SCALER_FMT_RGB565:
                     ctx->direct_pixconv = conv_bgr24_rgb565;
                  default:
                     break;
               }
               break;
            case SCALER_FMT_ARGB8888:
               switch (ctx->out_fmt)
               {
                  case SCALER_FMT_0RGB1555:
                     ctx->direct_pixconv = conv_argb8888_0rgb1555;
                     break;
                  case SCALER_FMT_BGR24:
                     ctx->direct_pixconv = conv_argb8888_bgr24;
                     break;
                  case SCALER_FMT_ABGR8888:
                     ctx->direct_pixconv = conv_argb8888_abgr8888;
                     break;
                  case SCALER_FMT_RGBA4444:
                     ctx->direct_pixconv = conv_argb8888_rgba4444;
                     break;
                  default:
                     break;
               }
               break;
            case SCALER_FMT_YUYV:
               switch (ctx->out_fmt)
               {
                  case SCALER_FMT_ARGB8888:
                     ctx->direct_pixconv = conv_yuyv_argb8888;
                     break;
                  default:
                     break;
               }
               break;
            case SCALER_FMT_RGBA4444:
               switch (ctx->out_fmt)
               {
                  case SCALER_FMT_ARGB8888:
                     ctx->direct_pixconv = conv_rgba4444_argb8888;
                     break;
                  case SCALER_FMT_RGB565:
                     ctx->direct_pixconv = conv_rgba4444_rgb565;
                     break;
                  default:
                     break;
               }
               break;
            case SCALER_FMT_ABGR8888:
               switch (ctx->out_fmt)
               {
                  case SCALER_FMT_BGR24:
                     ctx->direct_pixconv = conv_abgr8888_bgr24;
                     break;
                  default:
                     break;
               }
               break;
         }

         if (!ctx->direct_pixconv)
            return false;
      }
   }
   else
   {
      ctx->scaler_horiz = scaler_argb8888_horiz;
      ctx->scaler_vert  = scaler_argb8888_vert;

      switch (ctx->in_fmt)
      {
         case SCALER_FMT_ARGB8888:
            /* No need to convert :D */
            break;

         case SCALER_FMT_0RGB1555:
            ctx->in_pixconv = conv_0rgb1555_argb8888;
            break;

         case SCALER_FMT_RGB565:
            ctx->in_pixconv = conv_rgb565_argb8888;
            break;

         case SCALER_FMT_BGR24:
            ctx->in_pixconv = conv_bgr24_argb8888;
            break;

         case SCALER_FMT_RGBA4444:
            ctx->in_pixconv = conv_rgba4444_argb8888;
            break;

         default:
            return false;
      }

      switch (ctx->out_fmt)
      {
         case SCALER_FMT_ARGB8888:
            /* No need to convert :D */
            break;

         case SCALER_FMT_RGBA4444:
            ctx->out_pixconv = conv_argb8888_rgba4444;
            break;

         case SCALER_FMT_0RGB1555:
            ctx->out_pixconv = conv_argb8888_0rgb1555;
            break;

         case SCALER_FMT_BGR24:
            ctx->out_pixconv = conv_argb8888_bgr24;
            break;

         case SCALER_FMT_ABGR8888:
            ctx->out_pixconv = conv_argb8888_abgr8888;
            break;

         default:
            return false;
      }

      if (!scaler_gen_filter(ctx))
         return false;
   }

   return true;
}