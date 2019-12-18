#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct g2d_image {unsigned int width; unsigned int height; unsigned int stride; } ;
struct exynos_video {int font_color; int /*<<< orphan*/  font; TYPE_5__* font_driver; struct exynos_data* data; } ;
struct exynos_data {float aspect; struct g2d_image** src; } ;
struct TYPE_10__ {int video_msg_color_r; int video_msg_color_g; int video_msg_color_b; int /*<<< orphan*/  video_font_size; } ;
struct TYPE_9__ {scalar_t__* font_path; } ;
struct TYPE_8__ {int /*<<< orphan*/  video_font_enable; } ;
struct TYPE_11__ {TYPE_3__ floats; TYPE_2__ video; TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_13__ {unsigned int height; unsigned int bpp; int /*<<< orphan*/  buf_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t EXYNOS_IMAGE_FONT ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int const,unsigned int const) ; 
 unsigned int align_common (float,int) ; 
 TYPE_4__* config_get_ptr () ; 
 TYPE_6__* defaults ; 
 scalar_t__ exynos_realloc_buffer (struct exynos_data*,int /*<<< orphan*/ ,unsigned int const) ; 
 scalar_t__ font_renderer_create_default (TYPE_5__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_init_font(struct exynos_video *vid)
{
   struct exynos_data *pdata = vid->data;
   struct g2d_image *src     = pdata->src[EXYNOS_IMAGE_FONT];
   const unsigned buf_height = defaults[EXYNOS_IMAGE_FONT].height;
   const unsigned buf_width  = align_common(pdata->aspect * (float)buf_height, 16);
   const unsigned buf_bpp    = defaults[EXYNOS_IMAGE_FONT].bpp;
   settings_t *settings      = config_get_ptr();

   if (!settings->bools.video_font_enable)
      return 0;

   if (font_renderer_create_default(&vid->font_driver, &vid->font,
            *settings->video.font_path ? settings->video.font_path : NULL,
            settings->floats.video_font_size))
   {
      const int r = settings->floats.video_msg_color_r * 15;
      const int g = settings->floats.video_msg_color_g * 15;
      const int b = settings->floats.video_msg_color_b * 15;

      vid->font_color = ((b < 0 ? 0 : (b > 15 ? 15 : b)) << 0) |
         ((g < 0 ? 0 : (g > 15 ? 15 : g)) << 4) |
         ((r < 0 ? 0 : (r > 15 ? 15 : r)) << 8);
   }
   else
   {
      RARCH_ERR("[video_exynos]: creating font renderer failed\n");
      return -1;
   }

   /* The font buffer color type is ARGB4444. */
   if (exynos_realloc_buffer(pdata, defaults[EXYNOS_IMAGE_FONT].buf_type,
            buf_width * buf_height * buf_bpp) != 0)
   {
      vid->font_driver->free(vid->font);
      return -1;
   }

   src->width = buf_width;
   src->height = buf_height;
   src->stride = buf_width * buf_bpp;

#if (EXYNOS_GFX_DEBUG_LOG == 1)
   RARCH_LOG("[video_exynos]: using font rendering image with size %ux%u\n",
         buf_width, buf_height);
#endif

   return 0;
}