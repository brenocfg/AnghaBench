#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int height; unsigned int width; } ;
typedef  TYPE_4__ video_frame_info_t ;
struct string_list {unsigned int size; TYPE_1__* elems; } ;
typedef  scalar_t__ retro_time_t ;
struct TYPE_14__ {int /*<<< orphan*/  entries_label; } ;
struct TYPE_17__ {int osk_cursor; unsigned int entry_font_glyph_width; TYPE_3__* theme; TYPE_2__ fonts; } ;
typedef  TYPE_5__ ozone_handle_t ;
struct TYPE_18__ {unsigned int text_sublabel_rgba; } ;
struct TYPE_15__ {int /*<<< orphan*/  text_rgba; int /*<<< orphan*/ * textures; int /*<<< orphan*/  entries_border; } ;
struct TYPE_13__ {char* data; } ;

/* Variables and functions */
 scalar_t__ FONT_SIZE_ENTRIES_LABEL ; 
 scalar_t__ INTERVAL_OSK_CURSOR ; 
 size_t OZONE_THEME_TEXTURE_CURSOR_STATIC ; 
 int /*<<< orphan*/  TEXT_ALIGN_LEFT ; 
 scalar_t__ cpu_features_get_time_usec () ; 
 unsigned int font_driver_get_message_width (int /*<<< orphan*/ ,char const*,unsigned int,int) ; 
 int /*<<< orphan*/  menu_display_draw_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_draw_quad (TYPE_4__*,unsigned int,unsigned int,int,int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_event_get_osk_grid () ; 
 int /*<<< orphan*/  menu_event_get_osk_ptr () ; 
 int /*<<< orphan*/  ozone_draw_text (TYPE_4__*,TYPE_5__*,char const*,unsigned int,scalar_t__,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  ozone_osk_backdrop ; 
 int /*<<< orphan*/  ozone_pure_white ; 
 TYPE_6__ ozone_theme_light ; 
 int string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  word_wrap (char*,char const*,unsigned int,int,int /*<<< orphan*/ ) ; 

void ozone_draw_osk(ozone_handle_t *ozone,
      video_frame_info_t *video_info,
      const char *label, const char *str)
{
   unsigned i;
   const char *text;
   char message[2048];
   unsigned text_color;
   struct string_list *list;

   unsigned margin         = 75;
   unsigned padding        = 10;
   unsigned bottom_end     = video_info->height/2;
   unsigned y_offset       = 0;
   bool draw_placeholder   = string_is_empty(str);

   retro_time_t current_time      = cpu_features_get_time_usec();
   static retro_time_t last_time  = 0;

   if (current_time - last_time >= INTERVAL_OSK_CURSOR)
   {
      ozone->osk_cursor = !ozone->osk_cursor;
      last_time = current_time;
   }

   /* Border */
   /* Top */
   menu_display_draw_quad(video_info, margin, margin, video_info->width - margin*2, 1, video_info->width, video_info->height, ozone->theme->entries_border);

   /* Bottom */
   menu_display_draw_quad(video_info, margin, bottom_end - margin, video_info->width - margin*2, 1, video_info->width, video_info->height, ozone->theme->entries_border);

   /* Left */
   menu_display_draw_quad(video_info, margin, margin, 1, bottom_end - margin*2, video_info->width, video_info->height, ozone->theme->entries_border);

   /* Right */
   menu_display_draw_quad(video_info, video_info->width - margin, margin, 1, bottom_end - margin*2, video_info->width, video_info->height, ozone->theme->entries_border);

   /* Backdrop */
   /* TODO: Remove the backdrop if blur shader is available */
   menu_display_draw_quad(video_info, margin + 1, margin + 1, video_info->width - margin*2 - 2, bottom_end - margin*2 - 2, video_info->width, video_info->height, ozone_osk_backdrop);

   /* Placeholder & text*/
   if (!draw_placeholder)
   {
      text        = str;
      text_color  = 0xffffffff;
   }
   else
   {
      text        = label;
      text_color  = ozone_theme_light.text_sublabel_rgba;
   }

   word_wrap(message, text, (video_info->width - margin*2 - padding*2) / ozone->entry_font_glyph_width, true, 0);

   list = string_split(message, "\n");

   for (i = 0; i < list->size; i++)
   {
      const char *msg = list->elems[i].data;

      ozone_draw_text(video_info, ozone, msg, margin + padding * 2, margin + padding + FONT_SIZE_ENTRIES_LABEL + y_offset, TEXT_ALIGN_LEFT, video_info->width, video_info->height, ozone->fonts.entries_label, text_color, false);

      /* Cursor */
      if (i == list->size - 1)
      {
         if (ozone->osk_cursor)
         {
            unsigned cursor_x = draw_placeholder ? 0 : font_driver_get_message_width(ozone->fonts.entries_label, msg, (unsigned)strlen(msg), 1);
            menu_display_draw_quad(video_info, margin + padding*2 + cursor_x, margin + padding + y_offset + 3, 1, 25, video_info->width, video_info->height, ozone_pure_white);
         }
      }
      else
      {
         y_offset += 25;
      }
   }

   /* Keyboard */
   menu_display_draw_keyboard(
            ozone->theme->textures[OZONE_THEME_TEXTURE_CURSOR_STATIC],
            ozone->fonts.entries_label,
            video_info,
            menu_event_get_osk_grid(),
            menu_event_get_osk_ptr(),
            ozone->theme->text_rgba);

   string_list_free(list);
}