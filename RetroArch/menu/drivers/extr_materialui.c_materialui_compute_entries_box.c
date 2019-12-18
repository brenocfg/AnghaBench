#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int path_enabled; int label_enabled; int rich_label_enabled; int value_enabled; } ;
typedef  TYPE_6__ menu_entry_t ;
struct TYPE_20__ {float text_height; float entry_height; float y; size_t icon_texture_index; scalar_t__ has_icon; } ;
typedef  TYPE_7__ materialui_node_t ;
struct TYPE_17__ {unsigned int font_height; scalar_t__ glyph_width; } ;
struct TYPE_16__ {float font_height; } ;
struct TYPE_18__ {TYPE_4__ hint; TYPE_3__ list; } ;
struct TYPE_15__ {scalar_t__* list; } ;
struct TYPE_14__ {scalar_t__ width; } ;
struct TYPE_21__ {int margin; int landscape_entry_margin; scalar_t__ list_view_type; scalar_t__ thumbnail_height_max; int dip_base_unit_size; float content_height; TYPE_5__ font_data; scalar_t__ icon_size; TYPE_2__ textures; scalar_t__ thumbnail_width_max; scalar_t__ secondary_thumbnail_enabled; TYPE_1__ scrollbar; scalar_t__ is_portrait; scalar_t__ nav_bar_layout_width; } ;
typedef  TYPE_8__ materialui_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int MENU_SUBLABEL_MAX_LENGTH ; 
 scalar_t__ MUI_LIST_VIEW_DEFAULT ; 
 scalar_t__ MUI_LIST_VIEW_PLAYLIST ; 
 scalar_t__ MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int materialui_count_lines (char*) ; 
 int /*<<< orphan*/  materialui_scrollbar_init (TYPE_8__*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 size_t menu_entries_get_size () ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_6__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_get_sublabel (TYPE_6__*,char const**) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_6__*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  word_wrap (char*,char const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void materialui_compute_entries_box(
      materialui_handle_t* mui,
      unsigned width, unsigned height, unsigned header_height)
{
   unsigned i;
   int usable_width     =
            (int)width - (int)(mui->margin * 2) - (int)(mui->landscape_entry_margin * 2) - (int)mui->nav_bar_layout_width;
   file_list_t *list    = menu_entries_get_selection_buf_ptr(0);
   float sum            = 0;
   size_t entries_end   = menu_entries_get_size();

   /* If this is a playlist and the 'dual icon'
    * thumbnail view mode is enabled, each node has
    * a fixed height - and we can skip all the
    * usual calculations */
   if (mui->list_view_type == MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON)
   {
      /* One line of list text */
      float node_text_height  = (float)mui->font_data.list.font_height;
      /* List text + thumbnail height + padding */
      float node_entry_height =
            node_text_height + (float)mui->thumbnail_height_max +
            ((float)mui->dip_base_unit_size / 5.0f);

      for (i = 0; i < entries_end; i++)
      {
         materialui_node_t *node = (materialui_node_t*)
                  file_list_get_userdata_at_offset(list, i);

         node->text_height  = node_text_height;
         node->entry_height = node_entry_height;
         node->y            = sum;
         sum               += node_entry_height;
      }

      mui->content_height = sum;

      /* Total height is now known - can initialise scrollbar */
      materialui_scrollbar_init(mui, width, height, header_height);

      return;
   }

   /* If this is a playlist and any other thumbnail view
    * mode is enabled, must reduce usable width by
    * thumbnail width */
   if ((mui->list_view_type != MUI_LIST_VIEW_DEFAULT) &&
       (mui->list_view_type != MUI_LIST_VIEW_PLAYLIST))
   {
      int thumbnail_margin = 0;

      /* Account for additional padding in portrait mode */
      if (mui->is_portrait)
      {
         if (mui->secondary_thumbnail_enabled)
            thumbnail_margin = (int)mui->scrollbar.width;
      }
      /* Account for additional padding in landscape mode */
      else
         if (mui->landscape_entry_margin < mui->margin)
            thumbnail_margin = (int)(mui->margin - mui->landscape_entry_margin);

      usable_width -= mui->thumbnail_width_max + thumbnail_margin;

      /* Account for second thumbnail, if enabled */
      if (mui->secondary_thumbnail_enabled)
         usable_width -= mui->thumbnail_width_max + thumbnail_margin;
      /* If there is no second thumbnail and landscape
       * optimisations are active, increase width to
       * balance x offset of primary thumbnail */
      else if (mui->landscape_entry_margin > 0)
         usable_width += (mui->margin > mui->landscape_entry_margin) ?
               (int)mui->landscape_entry_margin : (int)mui->margin;
   }

   for (i = 0; i < entries_end; i++)
   {
      menu_entry_t entry;
      char wrapped_sublabel_str[MENU_SUBLABEL_MAX_LENGTH];
      const char *sublabel_str      = NULL;
      unsigned num_sublabel_lines   = 0;
      materialui_node_t *node       = (materialui_node_t*)
         file_list_get_userdata_at_offset(list, i);

      wrapped_sublabel_str[0] = '\0';

      menu_entry_init(&entry);
      entry.path_enabled       = false;
      entry.label_enabled      = false;
      entry.rich_label_enabled = false;
      entry.value_enabled      = false;
      menu_entry_get(&entry, 0, i, NULL, true);

      menu_entry_get_sublabel(&entry, &sublabel_str);

      if (!string_is_empty(sublabel_str))
      {
         int sublabel_width_max = usable_width;

         /* If this is a default menu list with an icon,
          * must subtract icon size from sublabel width */
         if (mui->list_view_type == MUI_LIST_VIEW_DEFAULT)
            if (node->has_icon)
               if (mui->textures.list[node->icon_texture_index])
                  sublabel_width_max -= (int)mui->icon_size;

         word_wrap(
               wrapped_sublabel_str, sublabel_str,
               sublabel_width_max / (int)mui->font_data.hint.glyph_width,
               false, 0);

         num_sublabel_lines = materialui_count_lines(wrapped_sublabel_str);
      }

      node->text_height  = mui->font_data.list.font_height +
            (num_sublabel_lines * mui->font_data.hint.font_height);

      node->entry_height = node->text_height +
            mui->dip_base_unit_size / 10;

      /* If this is a playlist and thumbnails are enabled,
       * must ensure that line_height is greater than
       * maximum thumbnail height */
      if ((mui->list_view_type != MUI_LIST_VIEW_DEFAULT) &&
          (mui->list_view_type != MUI_LIST_VIEW_PLAYLIST))
         node->entry_height = (node->entry_height < mui->thumbnail_height_max) ?
               mui->thumbnail_height_max : node->entry_height;

      node->entry_height      += mui->dip_base_unit_size / 10;
      node->y                  = sum;
      sum                     += node->entry_height;
   }

   mui->content_height = sum;

   /* Total height is now known - can initialise scrollbar */
   materialui_scrollbar_init(mui, width, height, header_height);
}