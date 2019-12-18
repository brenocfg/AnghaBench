#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  menu_entry_t ;
struct TYPE_20__ {int /*<<< orphan*/  secondary; int /*<<< orphan*/  primary; } ;
struct TYPE_21__ {unsigned int y; scalar_t__ entry_height; TYPE_6__ thumbnails; scalar_t__ text_height; } ;
typedef  TYPE_7__ materialui_node_t ;
struct TYPE_16__ {int /*<<< orphan*/  divider; int /*<<< orphan*/  list_hint_text; int /*<<< orphan*/  list_hint_text_highlighted; int /*<<< orphan*/  list_text; int /*<<< orphan*/  list_text_highlighted; } ;
struct TYPE_15__ {int glyph_width; int /*<<< orphan*/  font; } ;
struct TYPE_17__ {int glyph_width; scalar_t__ font_height; int /*<<< orphan*/  font; } ;
struct TYPE_18__ {TYPE_1__ hint; TYPE_3__ list; } ;
struct TYPE_14__ {int selected; char* s; size_t len; char const* str; } ;
struct TYPE_23__ {int selected; unsigned int field_width; char const* src_str; char* dst_str; int dst_str_len; int /*<<< orphan*/  font; } ;
struct TYPE_19__ {scalar_t__ width; } ;
struct TYPE_22__ {unsigned int scroll_y; int margin; int landscape_entry_margin; scalar_t__ list_view_type; TYPE_2__ colors; int /*<<< orphan*/  entry_divider_width; TYPE_4__ font_data; scalar_t__ ticker_x_offset; TYPE_10__ ticker; TYPE_9__ ticker_smooth; scalar_t__ use_smooth_ticker; scalar_t__ thumbnail_width_max; scalar_t__ nav_bar_layout_width; scalar_t__ secondary_thumbnail_enabled; TYPE_5__ scrollbar; scalar_t__ is_portrait; scalar_t__ thumbnail_height_max; } ;
typedef  TYPE_8__ materialui_handle_t ;
typedef  int /*<<< orphan*/  label_buf ;

/* Variables and functions */
 int MENU_SUBLABEL_MAX_LENGTH ; 
 scalar_t__ MUI_LIST_VIEW_PLAYLIST ; 
 scalar_t__ MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE ; 
 scalar_t__ MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM ; 
 int /*<<< orphan*/  TEXT_ALIGN_LEFT ; 
 int /*<<< orphan*/  materialui_draw_thumbnail (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float,unsigned int,unsigned int,float) ; 
 int /*<<< orphan*/  menu_animation_ticker (TYPE_10__*) ; 
 int /*<<< orphan*/  menu_animation_ticker_smooth (TYPE_9__*) ; 
 int /*<<< orphan*/  menu_display_draw_quad (int /*<<< orphan*/ *,float,int,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_draw_text (int /*<<< orphan*/ ,char*,int,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_entry_get_rich_label (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  menu_entry_get_sublabel (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  word_wrap (char*,char const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void materialui_render_menu_entry_playlist_list(
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
   const char *entry_label    = NULL;
   const char *entry_sublabel = NULL;
   int entry_y                = header_height - mui->scroll_y + node->y;
   int entry_margin           = (int)mui->margin + (int)mui->landscape_entry_margin;
   int usable_width           =
         (int)width - (int)(mui->margin * 2) - (int)(mui->landscape_entry_margin * 2) - (int)mui->nav_bar_layout_width;
   /* The label + sublabel text block is always drawn at
    * the vertical centre of the current node
    * Note: Text is drawn relative to the baseline,
    * so we can't do this accurately - but tests
    * indicate that the ascender of Material UI's
    * font accounts for 7/20 of its height, so we
    * just add (13/20) * font_height */
   int label_y                =
         entry_y + ((float)(node->entry_height - node->text_height) / 2.0f) +
         (13.0f * (float)mui->font_data.list.font_height / 20.0f);
   bool draw_text_outside     = (x_offset != 0);

   /* Initial ticker configuration
    * > Note: ticker is only used for labels,
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
   menu_entry_get_sublabel(entry, &entry_sublabel);

   /* Draw entry thumbnail(s)
    * > Has to be done first, since it affects the left
    *   hand margin size and total width for label +
    *   sublabel text */
   if (mui->list_view_type != MUI_LIST_VIEW_PLAYLIST)
   {
      int thumbnail_margin = 0;
      float thumbnail_y    =
            (float)entry_y + ((float)node->entry_height / 2.0f) - ((float)mui->thumbnail_height_max / 2.0f);

      /* When using portrait display orientations with
       * secondary thumbnails enabled, have to add a
       * left/right margin equal to the scroll bar
       * width (to prevent the scroll bar from being
       * drawn on top of the secondary thumbnail) */
      if (mui->is_portrait)
      {
         if (mui->secondary_thumbnail_enabled)
            thumbnail_margin = (int)mui->scrollbar.width;
      }
      /* When using landscape display orientations, we
       * have enough screen space to improve thumbnail
       * appearance by adding left/right margins - but
       * we only need to do this if landscape optimisations
       * are disabled (or landscape_entry_margin is less
       * than mui->margin) */
      else
         if (mui->landscape_entry_margin < mui->margin)
            thumbnail_margin = (int)(mui->margin - mui->landscape_entry_margin);

      /* Draw primary thumbnail */
      materialui_draw_thumbnail(
            mui,
            video_info,
            &node->thumbnails.primary,
            (float)(x_offset + thumbnail_margin + (int)mui->landscape_entry_margin),
            thumbnail_y,
            width,
            height,
            1.0f);

      entry_margin += mui->thumbnail_width_max + thumbnail_margin;
      usable_width -= mui->thumbnail_width_max + thumbnail_margin;

      /* Draw secondary thumbnail, if required */
      if (mui->secondary_thumbnail_enabled)
      {
         materialui_draw_thumbnail(
               mui,
               video_info,
               &node->thumbnails.secondary,
               (float)(x_offset + (int)width - thumbnail_margin - (int)mui->landscape_entry_margin -
                     (int)mui->nav_bar_layout_width - (int)mui->thumbnail_width_max),
               thumbnail_y,
               width,
               height,
               1.0f);

         usable_width -= mui->thumbnail_width_max + thumbnail_margin;
      }
      /* If there is no secondary thumbnail and landscape
       * optimisations are active, must increase usable width
       * to balance out the margin of the primary thumbnail
       * (since this is effectively left shifted when landscape
       * optimisations are active...) */
      else if (mui->landscape_entry_margin > 0)
         usable_width += (mui->margin > mui->landscape_entry_margin) ?
               (int)mui->landscape_entry_margin : (int)mui->margin;
   }

   /* Draw entry label */
   if (!string_is_empty(entry_label))
   {
      char label_buf[255];

      label_buf[0] = '\0';

      if (usable_width > 0)
      {
         /* Apply ticker */
         if (mui->use_smooth_ticker)
         {
            /* Label */
            mui->ticker_smooth.field_width = (unsigned)usable_width;
            mui->ticker_smooth.src_str     = entry_label;
            mui->ticker_smooth.dst_str     = label_buf;
            mui->ticker_smooth.dst_str_len = sizeof(label_buf);

            menu_animation_ticker_smooth(&mui->ticker_smooth);
         }
         else
         {
            /* Label */
            mui->ticker.s        = label_buf;
            mui->ticker.len      = (size_t)(usable_width / mui->font_data.list.glyph_width);
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

   /* Draw entry sublabel */
   if (!string_is_empty(entry_sublabel))
   {
      int sublabel_y = label_y + (int)mui->font_data.list.font_height;
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
   }

   /* When using the larger thumbnail views, the horizontal
    * text area is unpleasantly vacuous, such that the
    * label + sublabel strings float in a sea of nothingness.
    * We can partially mitigate the visual 'emptiness' of this
    * by drawing a divider between entries. This is particularly
    * beneficial when dual thumbnails are enabled, since it
    * 'ties' the left/right thumbnails together
    * NOTE: This does not work at all for the smallest thumbnail
    * list view, or when thumbnails are disabled - the result is
    * just too 'busy'/visually cluttered */
   if ((mui->list_view_type == MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM) ||
       (mui->list_view_type == MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE))
   {
      if (usable_width > 0)
         menu_display_draw_quad(
               video_info,
               (float)(x_offset + entry_margin),
               entry_y + (float)node->entry_height,
               (unsigned)usable_width,
               mui->entry_divider_width,
               width,
               height,
               mui->colors.divider);
   }
}