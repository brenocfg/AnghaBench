#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int wrap; scalar_t__ height; scalar_t__ position_y; } ;
typedef  TYPE_3__ ozone_node_t ;
struct TYPE_15__ {int entry_icon_padding; scalar_t__ thumbnail_bar_width; scalar_t__ sidebar_width; scalar_t__ entry_spacing; scalar_t__ entry_height; } ;
struct TYPE_14__ {int /*<<< orphan*/  entries_sublabel; } ;
struct TYPE_17__ {int empty_playlist; scalar_t__* icons_textures; int depth; int sublabel_font_glyph_width; size_t selection; scalar_t__ entries_height; TYPE_2__ dimensions; scalar_t__ show_thumbnail_bar; scalar_t__ is_playlist; TYPE_1__ fonts; } ;
typedef  TYPE_4__ ozone_handle_t ;
typedef  scalar_t__ menu_texture_item ;
struct TYPE_18__ {int path_enabled; int label_enabled; int rich_label_enabled; int value_enabled; int /*<<< orphan*/  type; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_5__ menu_entry_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENTRIES_CTL_START_GET ; 
 int MENU_SUBLABEL_MAX_LENGTH ; 
 size_t OZONE_ENTRIES_ICONS_TEXTURE_CORE_INFO ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,size_t) ; 
 unsigned int font_driver_get_line_height (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 size_t menu_entries_get_size () ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_5__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_get_sublabel (TYPE_5__*,char const**) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_5__*) ; 
 size_t menu_navigation_get_selection () ; 
 unsigned int ozone_count_lines (char*) ; 
 scalar_t__ ozone_entries_icon_get_texture (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ozone_get_entries_padding (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ozone_update_scroll (TYPE_4__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  word_wrap (char*,char const*,int,int,int /*<<< orphan*/ ) ; 

void ozone_compute_entries_position(ozone_handle_t *ozone)
{
   /* Compute entries height and adjust scrolling if needed */
   unsigned video_info_height;
   unsigned video_info_width;
   unsigned lines;
   size_t i, entries_end;

   file_list_t *selection_buf    = NULL;
   int entry_padding             = ozone_get_entries_padding(ozone, false);
   unsigned sublabel_line_height = font_driver_get_line_height(ozone->fonts.entries_sublabel, 1.0f);

   menu_entries_ctl(MENU_ENTRIES_CTL_START_GET, &i);

   entries_end   = menu_entries_get_size();
   selection_buf = menu_entries_get_selection_buf_ptr(0);

   video_driver_get_size(&video_info_width, &video_info_height);

   ozone->entries_height = 0;

   for (i = 0; i < entries_end; i++)
   {
      /* Entry */
      menu_entry_t entry;
      ozone_node_t *node       = NULL;
      const char *sublabel_str = NULL;

      menu_entry_init(&entry);
      entry.path_enabled       = false;
      entry.label_enabled      = false;
      entry.rich_label_enabled = false;
      entry.value_enabled      = false;
      menu_entry_get(&entry, 0, (unsigned)i, NULL, true);

      /* Empty playlist detection:
         only one item which icon is
         OZONE_ENTRIES_ICONS_TEXTURE_CORE_INFO */
      if (ozone->is_playlist && entries_end == 1)
      {
         menu_texture_item tex = ozone_entries_icon_get_texture(ozone, entry.enum_idx, entry.type, false);
         ozone->empty_playlist = tex == ozone->icons_textures[OZONE_ENTRIES_ICONS_TEXTURE_CORE_INFO];
      }
      else
      {
         ozone->empty_playlist = false;
      }

      /* Cache node */
      node = (ozone_node_t*)file_list_get_userdata_at_offset(selection_buf, i);

      if (!node)
         continue;

      node->height = ozone->dimensions.entry_height;
      node->wrap   = false;

      menu_entry_get_sublabel(&entry, &sublabel_str);

      if (!string_is_empty(sublabel_str))
      {
         int sublabel_max_width;
         char wrapped_sublabel_str[MENU_SUBLABEL_MAX_LENGTH];
         wrapped_sublabel_str[0] = '\0';

         node->height += ozone->dimensions.entry_spacing + 40;

         sublabel_max_width = video_info_width -
            entry_padding * 2 - ozone->dimensions.entry_icon_padding * 2;

         if (ozone->depth == 1)
            sublabel_max_width -= (unsigned) ozone->dimensions.sidebar_width;

         if (ozone->show_thumbnail_bar)
            sublabel_max_width -= ozone->dimensions.thumbnail_bar_width;

         word_wrap(wrapped_sublabel_str, sublabel_str, sublabel_max_width / ozone->sublabel_font_glyph_width, false, 0);

         lines = ozone_count_lines(wrapped_sublabel_str);

         if (lines > 1)
         {
            node->height += (lines - 1) * sublabel_line_height;
            node->wrap = true;
         }
      }

      node->position_y = ozone->entries_height;

      ozone->entries_height += node->height;
   }

   /* Update scrolling */
   ozone->selection = menu_navigation_get_selection();
   ozone_update_scroll(ozone, false, (ozone_node_t*) file_list_get_userdata_at_offset(selection_buf, ozone->selection));
}