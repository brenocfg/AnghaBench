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
struct g2d_image {unsigned int width; unsigned int height; unsigned int stride; int color_mode; unsigned char component_alpha; } ;
struct exynos_video {struct exynos_data* data; } ;
struct exynos_data {int /*<<< orphan*/  perf; TYPE_1__** buf; struct g2d_image** src; } ;
typedef  enum exynos_buffer_type { ____Placeholder_exynos_buffer_type } exynos_buffer_type ;
struct TYPE_4__ {int buf_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 size_t EXYNOS_IMAGE_MENU ; 
 int G2D_COLOR_FMT_ARGB4444 ; 
 int G2D_COLOR_FMT_ARGB8888 ; 
 int G2D_ORDER_RGBAX ; 
 TYPE_2__* defaults ; 
 int /*<<< orphan*/  exynos_perf_memcpy (int /*<<< orphan*/ *,int) ; 
 scalar_t__ exynos_realloc_buffer (struct exynos_data*,int const,unsigned int const) ; 
 int /*<<< orphan*/  memcpy_neon (int /*<<< orphan*/ ,void const*,unsigned int const) ; 

__attribute__((used)) static void exynos_set_texture_frame(void *data, const void *frame, bool rgb32,
      unsigned width, unsigned height, float alpha)
{
   const enum exynos_buffer_type buf_type = defaults[EXYNOS_IMAGE_MENU].buf_type;
   struct exynos_video *vid = data;
   struct exynos_data *pdata = vid->data;
   struct g2d_image *src = pdata->src[EXYNOS_IMAGE_MENU];
   const unsigned size = width * height * (rgb32 ? 4 : 2);

   if (exynos_realloc_buffer(pdata, buf_type, size) != 0)
      return;

   src->width = width;
   src->height = height;
   src->stride = width * (rgb32 ? 4 : 2);
   src->color_mode = rgb32 ? G2D_COLOR_FMT_ARGB8888 | G2D_ORDER_RGBAX :
      G2D_COLOR_FMT_ARGB4444 | G2D_ORDER_RGBAX;

   src->component_alpha = (unsigned char)(255.0f * alpha);

#if (EXYNOS_GFX_DEBUG_PERF == 1)
   exynos_perf_memcpy(&pdata->perf, true);
#endif

   memcpy_neon(pdata->buf[buf_type]->vaddr, frame, size);

#if (EXYNOS_GFX_DEBUG_PERF == 1)
   exynos_perf_memcpy(&pdata->perf, false);
#endif
}