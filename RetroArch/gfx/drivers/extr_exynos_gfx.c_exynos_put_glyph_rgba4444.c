#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct exynos_data {TYPE_2__** buf; TYPE_1__** src; } ;
typedef  enum exynos_image_type { ____Placeholder_exynos_image_type } exynos_image_type ;
struct TYPE_6__ {int buf_type; } ;
struct TYPE_5__ {scalar_t__ vaddr; } ;
struct TYPE_4__ {unsigned int width; } ;

/* Variables and functions */
 size_t EXYNOS_IMAGE_FONT ; 
 TYPE_3__* defaults ; 

__attribute__((used)) static void exynos_put_glyph_rgba4444(struct exynos_data *pdata,
      const uint8_t *__restrict__ src,
      uint16_t color, unsigned g_width, unsigned g_height,
      unsigned g_pitch, unsigned dst_x, unsigned dst_y)
{
   unsigned x, y;
   const enum exynos_image_type buf_type = defaults[EXYNOS_IMAGE_FONT].buf_type;
   const              unsigned buf_width = pdata->src[EXYNOS_IMAGE_FONT]->width;
   uint16_t            *__restrict__ dst = (uint16_t*)pdata->buf[buf_type]->vaddr +
      dst_y * buf_width + dst_x;

   for (y = 0; y < g_height; ++y, src += g_pitch, dst += buf_width)
   {
      for (x = 0; x < g_width; ++x)
      {
         const uint16_t blend = src[x];
         dst[x] = color | ((blend << 8) & 0xf000);
      }
   }
}