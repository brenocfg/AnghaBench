#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_16__ {scalar_t__ menu_rgui_aspect_ratio_lock; int /*<<< orphan*/  menu_rgui_aspect_ratio; } ;
struct TYPE_17__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_18__ {char* theme_preset_path; int bg_modified; int force_redraw; int /*<<< orphan*/  menu_video_settings; int /*<<< orphan*/  menu_aspect_ratio; } ;
typedef  TYPE_3__ rgui_t ;
struct TYPE_21__ {unsigned int height; int width; int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {int start_x; int start_y; unsigned int width; int height; unsigned int value_maxlen; } ;
struct TYPE_19__ {int max_width; int max_height; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int width; int height; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int FONT_HEIGHT_STRIDE ; 
 unsigned int FONT_WIDTH_STRIDE ; 
#define  RGUI_ASPECT_RATIO_16_10 131 
#define  RGUI_ASPECT_RATIO_16_10_CENTRE 130 
#define  RGUI_ASPECT_RATIO_16_9 129 
#define  RGUI_ASPECT_RATIO_16_9_CENTRE 128 
 scalar_t__ RGUI_ASPECT_RATIO_LOCK_NONE ; 
 scalar_t__ RGUI_ENTRY_VALUE_MAXLEN ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_2__* config_get_ptr () ; 
 TYPE_5__ fs_thumbnail ; 
 int /*<<< orphan*/  menu_display_get_fb_size (unsigned int*,unsigned int*,size_t*) ; 
 int /*<<< orphan*/  menu_display_set_framebuffer_pitch (int) ; 
 int /*<<< orphan*/  menu_display_set_height (int) ; 
 int /*<<< orphan*/  menu_display_set_width (int) ; 
 TYPE_5__ mini_left_thumbnail ; 
 TYPE_5__ mini_thumbnail ; 
 void* mini_thumbnail_max_height ; 
 void* mini_thumbnail_max_width ; 
 TYPE_10__ rgui_background_buf ; 
 int /*<<< orphan*/  rgui_background_free () ; 
 TYPE_9__ rgui_frame_buf ; 
 int /*<<< orphan*/  rgui_framebuffer_free () ; 
 int /*<<< orphan*/  rgui_set_video_config (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 TYPE_6__ rgui_term_layout ; 
 int /*<<< orphan*/  rgui_thumbnail_free (TYPE_5__*) ; 
 int /*<<< orphan*/  rgui_update_menu_viewport (TYPE_3__*) ; 

__attribute__((used)) static bool rgui_set_aspect_ratio(rgui_t *rgui, bool delay_update)
{
   unsigned base_term_width;
   settings_t *settings = config_get_ptr();
   
   rgui_framebuffer_free();
   rgui_background_free();
   rgui_thumbnail_free(&fs_thumbnail);
   rgui_thumbnail_free(&mini_thumbnail);
   rgui_thumbnail_free(&mini_left_thumbnail);
   
   /* Cache new aspect ratio */
   rgui->menu_aspect_ratio = settings->uints.menu_rgui_aspect_ratio;
   
#if defined(GEKKO)
   {
      size_t fb_pitch;
      unsigned fb_width, fb_height;
      
      menu_display_get_fb_size(&fb_width, &fb_height, &fb_pitch);
      
      /* Set frame buffer dimensions */
      rgui_frame_buf.height = fb_height;
      switch (rgui->menu_aspect_ratio)
      {
         /* Note: Maximum Wii framebuffer width is 424, not
          * the usual 426, since the last two bits of the
          * width value must be zero... */
         case RGUI_ASPECT_RATIO_16_9:
            if (rgui_frame_buf.height == 240)
               rgui_frame_buf.width = 424;
            else
               rgui_frame_buf.width = (unsigned)((16.0f / 9.0f) * (float)rgui_frame_buf.height) & ~3;
            base_term_width = rgui_frame_buf.width;
            break;
         case RGUI_ASPECT_RATIO_16_9_CENTRE:
            if (rgui_frame_buf.height == 240)
            {
               rgui_frame_buf.width = 424;
               base_term_width      = 320;
            }
            else
            {
               rgui_frame_buf.width = (unsigned)((16.0f / 9.0f) * (float)rgui_frame_buf.height) & ~3;
               base_term_width      = (unsigned)(( 4.0f / 3.0f) * (float)rgui_frame_buf.height) & ~3;
            }
            break;
         case RGUI_ASPECT_RATIO_16_10:
            if (rgui_frame_buf.height == 240)
               rgui_frame_buf.width = 384;
            else
               rgui_frame_buf.width = (unsigned)((16.0f / 10.0f) * (float)rgui_frame_buf.height) & ~3;
            base_term_width = rgui_frame_buf.width;
            break;
         case RGUI_ASPECT_RATIO_16_10_CENTRE:
            if (rgui_frame_buf.height == 240)
            {
               rgui_frame_buf.width = 384;
               base_term_width      = 320;
            }
            else
            {
               rgui_frame_buf.width = (unsigned)((16.0f / 10.0f) * (float)rgui_frame_buf.height) & ~3;
               base_term_width      = (unsigned)(( 4.0f / 3.0f)  * (float)rgui_frame_buf.height) & ~3;
            }
            break;
         default:
            /* 4:3 */
            if (rgui_frame_buf.height == 240)
               rgui_frame_buf.width = 320;
            else
               rgui_frame_buf.width = (unsigned)(( 4.0f / 3.0f)  * (float)rgui_frame_buf.height) & ~3;
            base_term_width = rgui_frame_buf.width;
            break;
      }
   }
#else
   /* Set frame buffer dimensions */
   rgui_frame_buf.height = 240;
   switch (rgui->menu_aspect_ratio)
   {
      case RGUI_ASPECT_RATIO_16_9:
         rgui_frame_buf.width = 426;
         base_term_width = rgui_frame_buf.width;
         break;
      case RGUI_ASPECT_RATIO_16_9_CENTRE:
         rgui_frame_buf.width = 426;
         base_term_width = 320;
         break;
      case RGUI_ASPECT_RATIO_16_10:
         rgui_frame_buf.width = 384;
         base_term_width = rgui_frame_buf.width;
         break;
      case RGUI_ASPECT_RATIO_16_10_CENTRE:
         rgui_frame_buf.width = 384;
         base_term_width = 320;
         break;
      default:
         /* 4:3 */
         rgui_frame_buf.width = 320;
         base_term_width = rgui_frame_buf.width;
         break;
   }
#endif
   
   /* Allocate frame buffer */
   rgui_frame_buf.data = (uint16_t*)calloc(
         rgui_frame_buf.width * rgui_frame_buf.height, sizeof(uint16_t));
   
   if (!rgui_frame_buf.data)
      return false;
   
   /* Configure 'menu display' settings */
   menu_display_set_width(rgui_frame_buf.width);
   menu_display_set_height(rgui_frame_buf.height);
   menu_display_set_framebuffer_pitch(rgui_frame_buf.width * sizeof(uint16_t));
   
   /* Determine terminal layout */
   rgui_term_layout.start_x = (3 * 5) + 1;
   rgui_term_layout.start_y = (3 * 5) + FONT_HEIGHT_STRIDE;
   rgui_term_layout.width = (base_term_width - (2 * rgui_term_layout.start_x)) / FONT_WIDTH_STRIDE;
   rgui_term_layout.height = (rgui_frame_buf.height - (2 * rgui_term_layout.start_y)) / FONT_HEIGHT_STRIDE;
   rgui_term_layout.value_maxlen = (unsigned)(((float)RGUI_ENTRY_VALUE_MAXLEN * (float)base_term_width / 320.0f) + 0.5);
   
   /* > 'Start X/Y' adjustments */
   rgui_term_layout.start_x = (rgui_frame_buf.width - (rgui_term_layout.width * FONT_WIDTH_STRIDE)) / 2;
   rgui_term_layout.start_y = (rgui_frame_buf.height - (rgui_term_layout.height * FONT_HEIGHT_STRIDE)) / 2;
   
   /* Allocate background buffer */
   rgui_background_buf.width = rgui_frame_buf.width;
   rgui_background_buf.height = rgui_frame_buf.height;
   rgui_background_buf.data = (uint16_t*)calloc(
         rgui_background_buf.width * rgui_background_buf.height, sizeof(uint16_t));
   
   if (!rgui_background_buf.data)
      return false;
   
   /* Allocate thumbnail buffer */
   fs_thumbnail.max_width = rgui_frame_buf.width;
   fs_thumbnail.max_height = rgui_frame_buf.height;
   fs_thumbnail.data = (uint16_t*)calloc(
         fs_thumbnail.max_width * fs_thumbnail.max_height, sizeof(uint16_t));
   if (!fs_thumbnail.data)
      return false;
   
   /* Allocate mini thumbnail buffers */
   mini_thumbnail_max_width = ((rgui_term_layout.width - 4) > 19 ? 19 : (rgui_term_layout.width - 4)) * FONT_WIDTH_STRIDE;
   mini_thumbnail_max_height = (unsigned)((rgui_term_layout.height * FONT_HEIGHT_STRIDE) * 0.5f) - 2;
   
   mini_thumbnail.max_width = mini_thumbnail_max_width;
   mini_thumbnail.max_height = mini_thumbnail_max_height;
   mini_thumbnail.data = (uint16_t*)calloc(
         mini_thumbnail.max_width * mini_thumbnail.max_height, sizeof(uint16_t));
   if (!mini_thumbnail.data)
      return false;
   
   mini_left_thumbnail.max_width = mini_thumbnail_max_width;
   mini_left_thumbnail.max_height = mini_thumbnail_max_height;
   mini_left_thumbnail.data = (uint16_t*)calloc(
         mini_left_thumbnail.max_width * mini_left_thumbnail.max_height, sizeof(uint16_t));
   if (!mini_left_thumbnail.data)
      return false;
   
   /* Trigger background/display update */
   rgui->theme_preset_path[0] = '\0';
   rgui->bg_modified = true;
   rgui->force_redraw = true;
   
   /* If aspect ratio lock is enabled, notify
    * video driver of change */
   if (settings->uints.menu_rgui_aspect_ratio_lock != RGUI_ASPECT_RATIO_LOCK_NONE)
   {
      rgui_update_menu_viewport(rgui);
      rgui_set_video_config(rgui, &rgui->menu_video_settings, delay_update);
   }
   
   return true;
}