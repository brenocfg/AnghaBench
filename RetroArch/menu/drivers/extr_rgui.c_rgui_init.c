#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct video_viewport {int /*<<< orphan*/  full_height; int /*<<< orphan*/  full_width; } ;
struct TYPE_12__ {int /*<<< orphan*/  menu_rgui_extended_ascii; int /*<<< orphan*/  menu_rgui_shadows; int /*<<< orphan*/  menu_rgui_border_filler_enable; int /*<<< orphan*/  menu_rgui_border_filler_thickness_enable; int /*<<< orphan*/  menu_rgui_background_filler_thickness_enable; } ;
struct TYPE_11__ {scalar_t__ menu_rgui_particle_effect; int /*<<< orphan*/  menu_rgui_aspect_ratio_lock; } ;
struct TYPE_13__ {TYPE_2__ bools; TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_14__ {char* menu_title; char* menu_sublabel; int aspect_update_pending; char* theme_preset_path; scalar_t__ particle_effect; int ignore_resize_events; int thumbnail_load_pending; int show_fs_thumbnail; int /*<<< orphan*/  pointer; scalar_t__ thumbnail_load_trigger_time; scalar_t__ left_thumbnail_queue_size; scalar_t__ thumbnail_queue_size; int /*<<< orphan*/  thumbnail_path_data; int /*<<< orphan*/  window_height; int /*<<< orphan*/  window_width; int /*<<< orphan*/  last_height; int /*<<< orphan*/  last_width; int /*<<< orphan*/  extended_ascii_enable; int /*<<< orphan*/  shadow_enable; int /*<<< orphan*/  border_enable; int /*<<< orphan*/  border_thickness; int /*<<< orphan*/  bg_thickness; scalar_t__ scroll_y; int /*<<< orphan*/  menu_aspect_ratio_lock; int /*<<< orphan*/  content_video_settings; scalar_t__ widgets_supported; } ;
typedef  TYPE_4__ rgui_t ;
typedef  int /*<<< orphan*/  menu_input_pointer_t ;
typedef  void menu_handle_t ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int FONT_HEIGHT_STRIDE ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_START ; 
 scalar_t__ RGUI_PARTICLE_EFFECT_NONE ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fs_thumbnail ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_allocate_white_texture () ; 
 int /*<<< orphan*/  menu_display_init_first_driver (int) ; 
 int /*<<< orphan*/  menu_display_set_header_height (unsigned int) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  menu_thumbnail_path_init () ; 
 scalar_t__ menu_widgets_ready () ; 
 int /*<<< orphan*/  mini_left_thumbnail ; 
 int /*<<< orphan*/  mini_thumbnail ; 
 int /*<<< orphan*/  prepare_rgui_colors (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  rgui_background_free () ; 
 TYPE_7__ rgui_frame_buf ; 
 int /*<<< orphan*/  rgui_framebuffer_free () ; 
 int /*<<< orphan*/  rgui_get_video_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rgui_init_font_lut () ; 
 int /*<<< orphan*/  rgui_init_particle_effect (TYPE_4__*) ; 
 int /*<<< orphan*/  rgui_set_aspect_ratio (TYPE_4__*,int) ; 
 int /*<<< orphan*/  rgui_set_blit_functions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgui_set_pixel_format_function () ; 
 int /*<<< orphan*/  rgui_thumbnail_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_get_viewport_info (struct video_viewport*) ; 

__attribute__((used)) static void *rgui_init(void **userdata, bool video_is_threaded)
{
   unsigned new_font_height;
   size_t start;
   struct video_viewport vp;
   rgui_t               *rgui = NULL;
   settings_t *settings       = config_get_ptr();
   menu_handle_t        *menu = (menu_handle_t*)calloc(1, sizeof(*menu));

   if (!menu)
      return NULL;

   rgui = (rgui_t*)calloc(1, sizeof(rgui_t));

   if (!rgui)
      goto error;

   *userdata              = rgui;

#if defined(HAVE_MENU_WIDGETS)
   /* We have to be somewhat careful here, since some
    * platforms do not like video_driver_texture-related
    * operations (e.g. 3DS). We would hope that these
    * platforms will always have HAVE_MENU_WIDGETS disabled,
    * but for extra safety we will only permit menu widget
    * additions when the current gfx driver reports that it
    * has widget support */
   rgui->widgets_supported = menu_widgets_ready();

   if (rgui->widgets_supported)
   {
      if (!menu_display_init_first_driver(video_is_threaded))
         goto error;

      menu_display_allocate_white_texture();
   }
#endif

   rgui->menu_title[0] = '\0';
   rgui->menu_sublabel[0] = '\0';

   /* Set pixel format conversion function */
   rgui_set_pixel_format_function();

   /* Cache initial video settings */
   rgui_get_video_config(&rgui->content_video_settings);

   /* Set aspect ratio
    * - Allocates frame buffer
    * - Configures variable 'menu display' settings */
   rgui->menu_aspect_ratio_lock = settings->uints.menu_rgui_aspect_ratio_lock;
   rgui->aspect_update_pending = false;
   if (!rgui_set_aspect_ratio(rgui, false))
      goto error;

   /* Fixed 'menu display' settings */
   new_font_height = FONT_HEIGHT_STRIDE * 2;
   menu_display_set_header_height(new_font_height);

   /* Prepare RGUI colors, to improve performance */
   rgui->theme_preset_path[0] = '\0';
   prepare_rgui_colors(rgui, settings);

   start = 0;
   menu_entries_ctl(MENU_ENTRIES_CTL_SET_START, &start);
   rgui->scroll_y = 0;

   rgui_init_font_lut();

   rgui->bg_thickness          = settings->bools.menu_rgui_background_filler_thickness_enable;
   rgui->border_thickness      = settings->bools.menu_rgui_border_filler_thickness_enable;
   rgui->border_enable         = settings->bools.menu_rgui_border_filler_enable;
   rgui->shadow_enable         = settings->bools.menu_rgui_shadows;
   rgui->particle_effect       = settings->uints.menu_rgui_particle_effect;
   rgui->extended_ascii_enable = settings->bools.menu_rgui_extended_ascii;

   rgui->last_width  = rgui_frame_buf.width;
   rgui->last_height = rgui_frame_buf.height;

   /* Get initial 'window' dimensions */
   video_driver_get_viewport_info(&vp);
   rgui->window_width         = vp.full_width;
   rgui->window_height        = vp.full_height;
   rgui->ignore_resize_events = false;

   /* Initialise particle effect, if required */
   if (rgui->particle_effect != RGUI_PARTICLE_EFFECT_NONE)
      rgui_init_particle_effect(rgui);

   /* Set initial 'blit_line/symbol' functions */
   rgui_set_blit_functions(
         settings->bools.menu_rgui_shadows, settings->bools.menu_rgui_extended_ascii);

   rgui->thumbnail_path_data = menu_thumbnail_path_init();
   if (!rgui->thumbnail_path_data)
      goto error;

   rgui->thumbnail_queue_size = 0;
   rgui->left_thumbnail_queue_size = 0;
   rgui->thumbnail_load_pending = false;
   rgui->thumbnail_load_trigger_time = 0;
   /* Ensure that we start with fullscreen thumbnails disabled */
   rgui->show_fs_thumbnail = false;

   /* Ensure that pointer device starts with well defined
    * values (shoult not be necessary, but some platforms may
    * not handle struct initialisation correctly...) */
   memset(&rgui->pointer, 0, sizeof(menu_input_pointer_t));

   return menu;

error:
   rgui_framebuffer_free();
   rgui_background_free();
   rgui_thumbnail_free(&fs_thumbnail);
   rgui_thumbnail_free(&mini_thumbnail);
   rgui_thumbnail_free(&mini_left_thumbnail);
   if (menu)
      free(menu);
   return NULL;
}