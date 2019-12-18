#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_12__ {scalar_t__ menu_materialui_thumbnail_background_enable; } ;
struct TYPE_14__ {TYPE_2__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_15__ {scalar_t__ status; int alpha; } ;
typedef  TYPE_5__ menu_thumbnail_t ;
struct TYPE_13__ {int /*<<< orphan*/  thumbnail_background; int /*<<< orphan*/  missing_thumbnail_icon; } ;
struct TYPE_11__ {int /*<<< orphan*/ * list; } ;
struct TYPE_16__ {int transition_alpha; scalar_t__ thumbnail_height_max; scalar_t__ thumbnail_width_max; TYPE_3__ colors; TYPE_1__ textures; scalar_t__ icon_size; } ;
typedef  TYPE_6__ materialui_handle_t ;

/* Variables and functions */
 scalar_t__ MENU_THUMBNAIL_STATUS_AVAILABLE ; 
 scalar_t__ MENU_THUMBNAIL_STATUS_MISSING ; 
 size_t MUI_TEXTURE_IMAGE ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  materialui_draw_icon (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,float,float,unsigned int,unsigned int,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_draw_quad (int /*<<< orphan*/ *,int,int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_set_alpha (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_thumbnail_draw (int /*<<< orphan*/ *,TYPE_5__*,float,float,scalar_t__,scalar_t__,int,float) ; 

__attribute__((used)) static void materialui_draw_thumbnail(
      materialui_handle_t *mui,
      video_frame_info_t *video_info,
      menu_thumbnail_t *thumbnail,
      float x, float y,
      unsigned width, unsigned height,
      float scale_factor)
{
   float bg_x;
   float bg_y;
   float bg_width;
   float bg_height;

   /* Sanity check */
   if (scale_factor <= 0)
      return;

   /* Get background draw position + dimensions,
    * accounting for scale factor */
   bg_width  = (float)mui->thumbnail_width_max * scale_factor;
   bg_height = (float)mui->thumbnail_height_max * scale_factor;
   bg_x      = x - (bg_width - (float)mui->thumbnail_width_max) / 2.0f;
   bg_y      = y - (bg_height - (float)mui->thumbnail_height_max) / 2.0f;

   /* If thumbnail is missing, draw fallback image... */
   if (thumbnail->status == MENU_THUMBNAIL_STATUS_MISSING)
   {
      float icon_size;

      /* Adjust icon size based on scale factor */
      if (scale_factor >= 1.0f)
         icon_size = (float)mui->icon_size;
      else
         icon_size = (float)mui->icon_size * scale_factor;

      /* Background */
      menu_display_set_alpha(
            mui->colors.thumbnail_background,
            mui->transition_alpha);

      menu_display_draw_quad(
            video_info,
            bg_x,
            bg_y,
            (unsigned)bg_width,
            (unsigned)bg_height,
            width,
            height,
            mui->colors.thumbnail_background);

      /* Icon */
      materialui_draw_icon(video_info,
            (unsigned)icon_size,
            mui->textures.list[MUI_TEXTURE_IMAGE],
            bg_x + (bg_width - icon_size) / 2.0f,
            bg_y + (bg_height - icon_size) / 2.0f,
            width,
            height,
            0.0f,
            1.0f,
            mui->colors.missing_thumbnail_icon);
   }
   /* If thumbnail is available, draw it
    * > Note that other conditions are ignored - i.e. we
    *   we draw nothing if thumbnail status is unknown,
    *   or we are waiting for a thumbnail to load) */
   else if (thumbnail->status == MENU_THUMBNAIL_STATUS_AVAILABLE)
   {
      settings_t *settings = config_get_ptr();

      if (!settings)
         return;

      /* Background */
      if (settings->bools.menu_materialui_thumbnail_background_enable)
      {
         /* > If enabled by the user, we draw a background here
          *   to ensure a uniform visual appearance regardless
          *   of thumbnail size
          * NOTE: Have to round up and add 1 to height,
          * otherwise background and thumbnail have obvious
          * misalignment (due to various rounding errors...) */

         /* > Set background alpha
          *   - Can't do this in materialui_colors_set_transition_alpha()
          *     because it's dependent upon thumbnail opacity
          *   - No need to restore the original alpha value, since it is
          *     only used in this function */
         menu_display_set_alpha(
               mui->colors.thumbnail_background,
               mui->transition_alpha * thumbnail->alpha);

         /* > Draw background quad */
         menu_display_draw_quad(
               video_info,
               (int)bg_x,
               (int)bg_y,
               (unsigned)(bg_width + 0.5f),
               (unsigned)(bg_height + 1.5f),
               width,
               height,
               mui->colors.thumbnail_background);
      }

      /* Thumbnail */
      menu_thumbnail_draw(
            video_info, thumbnail,
            x, y, mui->thumbnail_width_max, mui->thumbnail_height_max,
            mui->transition_alpha, scale_factor);
   }
}