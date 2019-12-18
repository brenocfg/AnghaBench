#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g2d_image {int color_mode; unsigned int width; unsigned int height; int stride; int color; int /*<<< orphan*/  repeat_mode; int /*<<< orphan*/ * bo; void* buf_type; } ;
struct g2d_context {int dummy; } ;
struct exynos_data {int bpp; unsigned int width; unsigned int height; int pitch; struct g2d_context* g2d; struct g2d_image* dst; struct g2d_image** src; TYPE_1__** buf; } ;
typedef  enum exynos_buffer_type { ____Placeholder_exynos_buffer_type } exynos_buffer_type ;
struct TYPE_4__ {int buf_type; unsigned int width; unsigned int height; unsigned int bpp; int g2d_color_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 unsigned int EXYNOS_IMAGE_COUNT ; 
 int G2D_COLOR_FMT_ARGB8888 ; 
 int G2D_COLOR_FMT_RGB565 ; 
 void* G2D_IMGBUF_GEM ; 
 int G2D_ORDER_AXRGB ; 
 int /*<<< orphan*/  G2D_REPEAT_MODE_PAD ; 
 struct g2d_image* calloc (int,int) ; 
 TYPE_2__* defaults ; 
 int /*<<< orphan*/  exynos_realloc_buffer (struct exynos_data*,int const,unsigned int const) ; 
 int /*<<< orphan*/  free (struct g2d_image*) ; 
 int /*<<< orphan*/  g2d_fini (struct g2d_context*) ; 
 struct g2d_context* g2d_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_drm_fd ; 

__attribute__((used)) static int exynos_g2d_init(struct exynos_data *pdata)
{
   unsigned i;
   struct g2d_image *dst = NULL;
   struct g2d_context *g2d = g2d_init(g_drm_fd);
   if (!g2d)
      return -1;

   dst = calloc(1, sizeof(struct g2d_image));
   if (!dst)
      goto fail;

   dst->buf_type   = G2D_IMGBUF_GEM;
   dst->color_mode = (pdata->bpp == 2) ? G2D_COLOR_FMT_RGB565 | G2D_ORDER_AXRGB :
      G2D_COLOR_FMT_ARGB8888 | G2D_ORDER_AXRGB;
   dst->width      = pdata->width;
   dst->height     = pdata->height;
   dst->stride     = pdata->pitch;
   dst->color      = 0xff000000; /* Clear color for solid fill operation. */

   for (i = 0; i < EXYNOS_IMAGE_COUNT; ++i)
   {
      const enum exynos_buffer_type buf_type = defaults[i].buf_type;
      const unsigned buf_size = defaults[i].width * defaults[i].height * defaults[i].bpp;
      struct g2d_image *src   = (struct g2d_image*)calloc(1, sizeof(struct g2d_image));
      if (!src)
         break;

      src->width       = defaults[i].width;
      src->height      = defaults[i].height;
      src->stride      = defaults[i].width * defaults[i].bpp;

      src->color_mode  = defaults[i].g2d_color_mode;

      /* Associate GEM buffer storage with G2D image. */
      src->buf_type    = G2D_IMGBUF_GEM;
      src->bo[0]       = pdata->buf[buf_type]->handle;

      src->repeat_mode = G2D_REPEAT_MODE_PAD; /* Pad creates no border artifacts. */

      /* Make sure that the storage buffer is large enough. If the code is working *
       * properly, then this is just a NOP. Still put it here as an insurance.     */
      exynos_realloc_buffer(pdata, buf_type, buf_size);

      pdata->src[i]    = src;
   }

   if (i != EXYNOS_IMAGE_COUNT)
   {
      while (i-- > 0)
      {
         free(pdata->src[i]);
         pdata->src[i] = NULL;
      }
      goto fail_src;
   }

   pdata->dst = dst;
   pdata->g2d = g2d;

   return 0;

fail_src:
   free(dst);

fail:
   g2d_fini(g2d);

   return -1;
}