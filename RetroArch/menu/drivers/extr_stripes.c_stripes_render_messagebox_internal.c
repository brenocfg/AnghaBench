#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_3__ video_frame_info_t ;
struct string_list {int size; TYPE_2__* elems; } ;
struct TYPE_14__ {int /*<<< orphan*/ * list; } ;
struct TYPE_17__ {int margins_dialog; TYPE_10__* font; TYPE_1__ textures; scalar_t__ margins_slice; } ;
typedef  TYPE_4__ stripes_handle_t ;
struct TYPE_15__ {char* data; } ;
struct TYPE_13__ {double size; } ;

/* Variables and functions */
 size_t STRIPES_TEXTURE_DIALOG_SLICE ; 
 int /*<<< orphan*/  TEXT_ALIGN_LEFT ; 
 int font_driver_get_message_width (TYPE_10__*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_blend_begin (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_display_draw_text (TYPE_10__*,char const*,int,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_display_draw_texture_slice (TYPE_3__*,int,scalar_t__,int,int,int,float,unsigned int,unsigned int,int /*<<< orphan*/ *,scalar_t__,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_event_get_osk_grid () ; 
 int /*<<< orphan*/  menu_event_get_osk_ptr () ; 
 scalar_t__ menu_input_dialog_get_display_kb () ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char const*,char*) ; 
 int /*<<< orphan*/  stripes_render_keyboard (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ utf8len (char const*) ; 

__attribute__((used)) static void stripes_render_messagebox_internal(
      video_frame_info_t *video_info,
      stripes_handle_t *stripes, const char *message)
{
   unsigned i, y_position;
   int x, y, longest = 0, longest_width = 0;
   float line_height        = 0;
   unsigned width           = video_info->width;
   unsigned height          = video_info->height;
   struct string_list *list = !string_is_empty(message)
      ? string_split(message, "\n") : NULL;

   if (!list || !stripes || !stripes->font)
   {
      if (list)
         string_list_free(list);
      return;
   }

   if (list->elems == 0)
      goto end;

   line_height      = stripes->font->size * 1.2;

   y_position       = height / 2;
   if (menu_input_dialog_get_display_kb())
      y_position    = height / 4;

   x                = width  / 2;
   y                = y_position - (list->size-1) * line_height / 2;

   /* find the longest line width */
   for (i = 0; i < list->size; i++)
   {
      const char *msg  = list->elems[i].data;
      int len          = (int)utf8len(msg);

      if (len > longest)
      {
         longest       = len;
         longest_width = font_driver_get_message_width(
               stripes->font, msg, strlen(msg), 1);
      }
   }

   menu_display_blend_begin(video_info);

   menu_display_draw_texture_slice(
         video_info,
         x - longest_width/2 - stripes->margins_dialog,
         y + stripes->margins_slice - stripes->margins_dialog,
         256, 256,
         longest_width + stripes->margins_dialog * 2,
         line_height * list->size + stripes->margins_dialog * 2,
         width, height,
         NULL,
         stripes->margins_slice, 1.0,
         stripes->textures.list[STRIPES_TEXTURE_DIALOG_SLICE]);

   for (i = 0; i < list->size; i++)
   {
      const char *msg = list->elems[i].data;

      if (msg)
         menu_display_draw_text(stripes->font, msg,
               x - longest_width/2.0,
               y + (i+0.75) * line_height,
               width, height, 0x444444ff, TEXT_ALIGN_LEFT, 1.0f, false, 0, false);
   }

   if (menu_input_dialog_get_display_kb())
      stripes_render_keyboard(stripes,
            video_info,
            menu_event_get_osk_grid(),
            menu_event_get_osk_ptr());

end:
   string_list_free(list);
}