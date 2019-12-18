#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  value_buf ;
struct TYPE_27__ {int /*<<< orphan*/  checked; } ;
typedef  TYPE_6__ menu_entry_t ;
struct TYPE_28__ {unsigned int y; int has_icon; size_t icon_texture_index; float entry_height; } ;
typedef  TYPE_7__ materialui_node_t ;
struct TYPE_26__ {int /*<<< orphan*/  list_text; int /*<<< orphan*/  list_text_highlighted; int /*<<< orphan*/  list_switch_on; int /*<<< orphan*/  list_hint_text; int /*<<< orphan*/  list_hint_text_highlighted; int /*<<< orphan*/  list_icon; } ;
struct TYPE_24__ {float font_height; unsigned int glyph_width; int /*<<< orphan*/  font; } ;
struct TYPE_22__ {int glyph_width; int /*<<< orphan*/  font; } ;
struct TYPE_25__ {TYPE_3__ list; TYPE_1__ hint; } ;
struct TYPE_21__ {int selected; char* s; size_t len; char const* str; } ;
struct TYPE_20__ {int selected; unsigned int field_width; char const* src_str; char* dst_str; int dst_str_len; int /*<<< orphan*/  font; } ;
struct TYPE_23__ {uintptr_t* list; } ;
struct TYPE_29__ {unsigned int scroll_y; int margin; int landscape_entry_margin; float icon_size; float dip_base_unit_size; unsigned int ticker_x_offset; unsigned int ticker_str_width; TYPE_5__ colors; TYPE_4__ font_data; TYPE_14__ ticker; TYPE_13__ ticker_smooth; scalar_t__ use_smooth_ticker; scalar_t__ nav_bar_layout_width; TYPE_2__ textures; } ;
typedef  TYPE_8__ materialui_handle_t ;
typedef  int /*<<< orphan*/  label_buf ;
typedef  enum msg_file_type { ____Placeholder_msg_file_type } msg_file_type ;
typedef  enum materialui_entry_value_type { ____Placeholder_materialui_entry_value_type } materialui_entry_value_type ;

/* Variables and functions */
#define  FILE_TYPE_COMPRESSED 133 
#define  FILE_TYPE_IMAGE 132 
 int FILE_TYPE_NONE ; 
 unsigned int MENU_SETTING_DROPDOWN_ITEM ; 
 unsigned int MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM_SPECIAL ; 
 int MENU_SUBLABEL_MAX_LENGTH ; 
#define  MUI_ENTRY_VALUE_CHECKMARK 131 
 int MUI_ENTRY_VALUE_NONE ; 
#define  MUI_ENTRY_VALUE_SWITCH_OFF 130 
#define  MUI_ENTRY_VALUE_SWITCH_ON 129 
#define  MUI_ENTRY_VALUE_TEXT 128 
 size_t MUI_TEXTURE_ARCHIVE ; 
 size_t MUI_TEXTURE_CHECKMARK ; 
 size_t MUI_TEXTURE_IMAGE ; 
 int /*<<< orphan*/  TEXT_ALIGN_LEFT ; 
 int /*<<< orphan*/  TEXT_ALIGN_RIGHT ; 
 int /*<<< orphan*/  materialui_draw_icon (int /*<<< orphan*/ *,float,uintptr_t,int,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int materialui_get_entry_value_type (TYPE_8__*,char const*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  materialui_render_switch_icon (TYPE_8__*,int /*<<< orphan*/ *,int,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  menu_animation_ticker (TYPE_14__*) ; 
 int /*<<< orphan*/  menu_animation_ticker_smooth (TYPE_13__*) ; 
 int /*<<< orphan*/  menu_display_draw_text (int /*<<< orphan*/ ,char*,int,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_entry_get_rich_label (TYPE_6__*,char const**) ; 
 int /*<<< orphan*/  menu_entry_get_sublabel (TYPE_6__*,char const**) ; 
 unsigned int menu_entry_get_type_new (TYPE_6__*) ; 
 int /*<<< orphan*/  menu_entry_get_value (TYPE_6__*,char const**) ; 
 int /*<<< orphan*/  msg_hash_calculate (char const*) ; 
 int msg_hash_to_file_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 size_t utf8len (char const*) ; 
 int /*<<< orphan*/  word_wrap (char*,char const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void materialui_render_menu_entry_default(
      materialui_handle_t *mui,
      video_frame_info_t *video_info,
      materialui_node_t *node,
      menu_entry_t *entry,
      bool entry_selected,
      bool touch_feedback_active,
      unsigned header_height,
      unsigned width, unsigned height,
      int x_offset)
{
   const char *entry_value                           = NULL;
   const char *entry_label                           = NULL;
   const char *entry_sublabel                        = NULL;
   unsigned entry_type                               = 0;
   enum materialui_entry_value_type entry_value_type = MUI_ENTRY_VALUE_NONE;
   unsigned entry_value_width                        = 0;
   enum msg_file_type entry_file_type                = FILE_TYPE_NONE;
   int entry_y                                       = header_height - mui->scroll_y + node->y;
   int entry_margin                                  = (int)mui->margin + (int)mui->landscape_entry_margin;
   int usable_width                                  =
         (int)width - (int)(mui->margin * 2) - (int)(mui->landscape_entry_margin * 2) - (int)mui->nav_bar_layout_width;
   int label_y                                       = 0;
   int value_icon_y                                  = 0;
   uintptr_t icon_texture                            = 0;
   bool draw_text_outside                            = (x_offset != 0);

   /* Initial ticker configuration
    * > Note: ticker is only used for labels/values,
    *   not sublabel text */
   if (mui->use_smooth_ticker)
   {
      mui->ticker_smooth.font     = mui->font_data.list.font;
      mui->ticker_smooth.selected = entry_selected;
   }
   else
      mui->ticker.selected = entry_selected;

   /* Read entry parameters */
   menu_entry_get_rich_label(entry, &entry_label);
   menu_entry_get_value(entry, &entry_value);
   menu_entry_get_sublabel(entry, &entry_sublabel);
   entry_type = menu_entry_get_type_new(entry);

   entry_file_type = msg_hash_to_file_type(msg_hash_calculate(entry_value));
   entry_value_type = materialui_get_entry_value_type(
         mui, entry_value, entry->checked, entry_type, entry_file_type);

   /* Draw entry icon
    * > Has to be done first, since it affects the left
    *   hand margin size for label + sublabel text */
   if (node->has_icon)
   {
      if (entry->checked &&
          ((entry_type >= MENU_SETTING_DROPDOWN_ITEM) &&
           (entry_type <= MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM_SPECIAL)))
         node->has_icon = false;
      else
         icon_texture = mui->textures.list[node->icon_texture_index];
   }
   else
   {
      switch (entry_file_type)
      {
         case FILE_TYPE_COMPRESSED:
            icon_texture = mui->textures.list[MUI_TEXTURE_ARCHIVE];
            break;
         case FILE_TYPE_IMAGE:
            icon_texture = mui->textures.list[MUI_TEXTURE_IMAGE];
            break;
         default:
            break;
      }
   }

   if (icon_texture)
   {
      materialui_draw_icon(video_info,
            mui->icon_size,
            (uintptr_t)icon_texture,
            x_offset + (int)mui->landscape_entry_margin,
            entry_y + (node->entry_height / 2.0f) - (mui->icon_size / 2.0f),
            width,
            height,
            0,
            1,
            mui->colors.list_icon);

      entry_margin += mui->icon_size;
      usable_width -= mui->icon_size;
   }

   /* Draw entry sublabel
    * > Must be done before label + value, since it
    *   affects y offset positions */
   if (!string_is_empty(entry_sublabel))
   {
      int sublabel_y =
            entry_y + (int)(mui->dip_base_unit_size / 5.0f) +
                  (int)mui->font_data.list.font_height;
      char wrapped_sublabel[MENU_SUBLABEL_MAX_LENGTH];

      wrapped_sublabel[0] = '\0';

      /* Wrap sublabel string */
      word_wrap(wrapped_sublabel, entry_sublabel,
            (int)(usable_width / mui->font_data.hint.glyph_width),
            true, 0);

      /* Draw sublabel string
       * > Note: We must allow text to be drawn off-screen
       *   if the current y position is negative, otherwise topmost
       *   entries with very long sublabels may get 'clipped' too
       *   early as they are scrolled upwards beyond the top edge
       *   of the screen */
      menu_display_draw_text(mui->font_data.hint.font, wrapped_sublabel,
            x_offset + entry_margin,
            sublabel_y,
            width, height,
            (entry_selected || touch_feedback_active) ?
                  mui->colors.list_hint_text_highlighted : mui->colors.list_hint_text,
            TEXT_ALIGN_LEFT, 1.0f, false, 0, draw_text_outside || (sublabel_y < 0));

      /* If we have a sublabel, entry label y position has a
       * fixed vertical offset */
      label_y      = entry_y + (int)(mui->dip_base_unit_size / 5.0f);
      value_icon_y = entry_y + (int)((mui->dip_base_unit_size / 6.0f) - (mui->icon_size / 2.0f));
   }
   else
   {
      /* If we don't have a sublabel, entry label is drawn
       * at the vertical centre of the current node
       * Note: Text is drawn relative to the baseline,
       * so we can't do this accurately - but as a general
       * rule of thumb, the descender of a font is at least
       * 20% of it's height - so we just add (font_height / 5) */
      label_y      = entry_y + (int)((node->entry_height / 2.0f) + (mui->font_data.list.font_height / 5.0f));
      value_icon_y = entry_y + (int)((node->entry_height / 2.0f) - (mui->icon_size / 2.0f));
   }

   /* Draw entry value */
   switch (entry_value_type)
   {
      case MUI_ENTRY_VALUE_TEXT:
         {
            int value_x_offset             = 0;
            unsigned entry_value_width_max = (usable_width / 2) - mui->margin;
            char value_buf[255];

            value_buf[0] = '\0';

            /* Apply ticker */
            if (mui->use_smooth_ticker)
            {
               mui->ticker_smooth.field_width = entry_value_width_max;
               mui->ticker_smooth.src_str     = entry_value;
               mui->ticker_smooth.dst_str     = value_buf;
               mui->ticker_smooth.dst_str_len = sizeof(value_buf);

               if (menu_animation_ticker_smooth(&mui->ticker_smooth))
               {
                  /* If ticker is active, then value text is effectively
                   * entry_value_width_max pixels wide... */
                  entry_value_width = entry_value_width_max;
                  /* ...and since value text is right aligned, have to
                   * offset x position by the 'padding' width at the
                   * end of the ticker string */
                  value_x_offset =
                        (int)(mui->ticker_x_offset + mui->ticker_str_width) -
                              (int)entry_value_width_max;
               }
               /* If ticker is inactive, width of value string is
                * exactly mui->ticker_str_width pixels, and no x offset
                * is required */
               else
                  entry_value_width = mui->ticker_str_width;
            }
            else
            {
               size_t entry_value_len     = utf8len(entry_value);
               size_t entry_value_len_max =
                     (size_t)(entry_value_width_max / mui->font_data.list.glyph_width);

               /* Limit length of value string */
               entry_value_len_max = (entry_value_len_max > 0) ?
                     entry_value_len_max - 1 : entry_value_len_max;
               entry_value_len = (entry_value_len > entry_value_len_max) ?
                     entry_value_len_max : entry_value_len;

               mui->ticker.s        = value_buf;
               mui->ticker.len      = entry_value_len;
               mui->ticker.str      = entry_value;

               menu_animation_ticker(&mui->ticker);

               /* Get effective width of value string
                * > Approximate value - only the smooth ticker
                *   returns the actual width in pixels, and any
                *   platform too slow to run the smooth ticker
                *   won't appreciate the overheads of using
                *   font_driver_get_message_width() here... */
               entry_value_width = (entry_value_len + 1) * mui->font_data.list.glyph_width;
            }

            /* Draw value string */
            menu_display_draw_text(mui->font_data.list.font, value_buf,
                  x_offset + value_x_offset + (int)width - (int)mui->margin - (int)mui->landscape_entry_margin - (int)mui->nav_bar_layout_width,
                  label_y,
                  width, height,
                  (entry_selected || touch_feedback_active) ?
                        mui->colors.list_text_highlighted : mui->colors.list_text,
                  TEXT_ALIGN_RIGHT, 1.0f, false, 0, draw_text_outside);
         }
         break;
      case MUI_ENTRY_VALUE_SWITCH_ON:
         {
            materialui_render_switch_icon(
                  mui, video_info, value_icon_y, width, height, x_offset, true);
            entry_value_width = mui->icon_size;
         }
         break;
      case MUI_ENTRY_VALUE_SWITCH_OFF:
         {
            materialui_render_switch_icon(
                  mui, video_info, value_icon_y, width, height, x_offset, false);
            entry_value_width = mui->icon_size;
         }
         break;
      case MUI_ENTRY_VALUE_CHECKMARK:
         {
            /* Draw checkmark */
            if (mui->textures.list[MUI_TEXTURE_CHECKMARK])
               materialui_draw_icon(video_info,
                     mui->icon_size,
                     mui->textures.list[MUI_TEXTURE_CHECKMARK],
                     x_offset + (int)width - (int)mui->margin - (int)mui->landscape_entry_margin - (int)mui->nav_bar_layout_width - (int)mui->icon_size,
                     value_icon_y,
                     width,
                     height,
                     0,
                     1,
                     mui->colors.list_switch_on);

            entry_value_width = mui->icon_size;
         }
         break;
      default:
         entry_value_width = 0;
         break;
   }

   /* Draw entry label */
   if (!string_is_empty(entry_label))
   {
      int label_width = usable_width;
      char label_buf[255];

      label_buf[0] = '\0';

      /* Get maximum width of label string
       * > If a value is present, need additional padding
       *   between label and value */
      label_width = (entry_value_width > 0) ?
            label_width - (int)(entry_value_width + mui->margin) : label_width;

      if (label_width > 0)
      {
         /* Apply ticker */
         if (mui->use_smooth_ticker)
         {
            /* Label */
            mui->ticker_smooth.field_width = (unsigned)label_width;
            mui->ticker_smooth.src_str     = entry_label;
            mui->ticker_smooth.dst_str     = label_buf;
            mui->ticker_smooth.dst_str_len = sizeof(label_buf);

            menu_animation_ticker_smooth(&mui->ticker_smooth);
         }
         else
         {
            /* Label */
            mui->ticker.s        = label_buf;
            mui->ticker.len      = (size_t)(label_width / mui->font_data.list.glyph_width);
            mui->ticker.str      = entry_label;

            menu_animation_ticker(&mui->ticker);
         }

         /* Draw label string */
         menu_display_draw_text(mui->font_data.list.font, label_buf,
               x_offset + (int)mui->ticker_x_offset + entry_margin,
               label_y,
               width, height,
               (entry_selected || touch_feedback_active) ?
                     mui->colors.list_text_highlighted : mui->colors.list_text,
               TEXT_ALIGN_LEFT, 1.0f, false, 0, draw_text_outside);
      }
   }
}