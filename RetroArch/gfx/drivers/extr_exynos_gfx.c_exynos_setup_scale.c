#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g2d_image {unsigned int width; unsigned int height; int color_mode; } ;
struct exynos_data {float const aspect; unsigned int width; unsigned int height; unsigned int* blit_params; unsigned int num_pages; TYPE_1__* pages; struct g2d_image** src; } ;
struct TYPE_2__ {int clear; } ;

/* Variables and functions */
 size_t EXYNOS_IMAGE_FRAME ; 
 int G2D_COLOR_FMT_RGB565 ; 
 int G2D_COLOR_FMT_XRGB8888 ; 
 int G2D_ORDER_AXRGB ; 
 float fabsf (float const) ; 

__attribute__((used)) static void exynos_setup_scale(struct exynos_data *pdata,
      unsigned width, unsigned height, unsigned src_bpp)
{
   unsigned i;
   unsigned w, h;
   struct g2d_image *src = pdata->src[EXYNOS_IMAGE_FRAME];
   const float aspect = (float)width / (float)height;

   src->width      = width;
   src->height     = height;
   src->color_mode = (src_bpp == 2) ?
      G2D_COLOR_FMT_RGB565 | G2D_ORDER_AXRGB:
      G2D_COLOR_FMT_XRGB8888 | G2D_ORDER_AXRGB;

   if (fabsf(pdata->aspect - aspect) < 0.0001f)
   {
      w = pdata->width;
      h = pdata->height;
   }
   else
   {
      if (pdata->aspect > aspect)
      {
         w = (float)pdata->width * aspect / pdata->aspect;
         h = pdata->height;
      }
      else
      {
         w = pdata->width;
         h = (float)pdata->height * pdata->aspect / aspect;
      }
   }

   pdata->blit_params[0] = (pdata->width - w) / 2;
   pdata->blit_params[1] = (pdata->height - h) / 2;
   pdata->blit_params[2] = w;
   pdata->blit_params[3] = h;
   pdata->blit_params[4] = width;
   pdata->blit_params[5] = height;

   for (i = 0; i < pdata->num_pages; ++i)
      pdata->pages[i].clear = true;
}