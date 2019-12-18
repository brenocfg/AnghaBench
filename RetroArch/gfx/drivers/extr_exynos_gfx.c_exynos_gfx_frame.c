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
struct TYPE_5__ {int /*<<< orphan*/  osd_stat_params; int /*<<< orphan*/  stat_text; scalar_t__ statistics_show; } ;
typedef  TYPE_1__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct font_params {int dummy; } ;
struct exynos_video {unsigned int width; unsigned int height; int /*<<< orphan*/  data; int /*<<< orphan*/  menu_rotation; scalar_t__ menu_active; int /*<<< orphan*/  bytes_per_pixel; } ;
struct exynos_page {int clear; int used; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ exynos_blend_menu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exynos_blit_frame (int /*<<< orphan*/ ,void const*,unsigned int) ; 
 scalar_t__ exynos_flip (int /*<<< orphan*/ ,struct exynos_page*) ; 
 struct exynos_page* exynos_free_page (int /*<<< orphan*/ ) ; 
 scalar_t__ exynos_render_msg (struct exynos_video*,char const*) ; 
 int /*<<< orphan*/  exynos_set_fake_blit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_setup_scale (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  font_driver_render_msg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct font_params const*) ; 
 int /*<<< orphan*/  menu_driver_frame (TYPE_1__*) ; 

__attribute__((used)) static bool exynos_gfx_frame(void *data, const void *frame, unsigned width,
      unsigned height, uint64_t frame_count, unsigned pitch, const char *msg,
      video_frame_info_t *video_info)
{
   struct exynos_video *vid = data;
   struct exynos_page *page = NULL;

   /* Check if neither menu nor core framebuffer is to be displayed. */
   if (!vid->menu_active && !frame)
      return true;

   if (frame != NULL)
   {
      if (width != vid->width || height != vid->height)
      {
         /* Sanity check on new dimension parameters. */
         if (width == 0 || height == 0)
            return true;

         RARCH_LOG("[video_exynos]: resolution changed by core: %ux%u -> %ux%u\n",
               vid->width, vid->height, width, height);
         exynos_setup_scale(vid->data, width, height, vid->bytes_per_pixel);

         vid->width = width;
         vid->height = height;
      }

      page = exynos_free_page(vid->data);

      if (exynos_blit_frame(vid->data, frame, pitch) != 0)
         goto fail;
   }

   /* If at this point the dimension parameters are still zero, setup some  *
    * fake blit parameters so that menu and font rendering work properly.   */
   if (vid->width == 0 || vid->height == 0)
      exynos_set_fake_blit(vid->data);

   if (!page)
      page = exynos_free_page(vid->data);

   if (vid->menu_active)
   {
      if (exynos_blend_menu(vid->data, vid->menu_rotation) != 0)
         goto fail;
#ifdef HAVE_MENU
      menu_driver_frame(video_info);
#endif
   }
   else if (video_info->statistics_show)
   {
      struct font_params *osd_params = video_info ?
         (struct font_params*)&video_info->osd_stat_params : NULL;

      if (osd_params)
      {
         font_driver_render_msg(video_info, NULL, video_info->stat_text,
               (const struct font_params*)&video_info->osd_stat_params);
      }
   }

   if (msg)
   {
      if (exynos_render_msg(vid, msg) != 0)
         goto fail;

      /* Font is blitted to the entire screen, so issue clear afterwards. */
      page->clear = true;
   }

   if (exynos_flip(vid->data, page) != 0)
      goto fail;

   return true;

fail:
   /* Since we didn't manage to issue a pageflip to this page, set *
    * it to 'unused' again, and hope that it works next time.      */
   page->used = false;

   return false;
}