#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_15__ {int path_enabled; int value_enabled; int sublabel_enabled; } ;
typedef  TYPE_2__ menu_entry_t ;
typedef  int /*<<< orphan*/  materialui_node_t ;
struct TYPE_14__ {int /*<<< orphan*/  dragged; } ;
struct TYPE_16__ {float touch_feedback_alpha; size_t touch_feedback_selection; size_t first_onscreen_entry; size_t last_onscreen_entry; int list_view_type; TYPE_1__ scrollbar; } ;
typedef  TYPE_3__ materialui_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
#define  MUI_LIST_VIEW_DEFAULT 133 
#define  MUI_LIST_VIEW_PLAYLIST 132 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON 131 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE 130 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM 129 
#define  MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL 128 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  materialui_render_menu_entry_default (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  materialui_render_menu_entry_playlist_dual_icon (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  materialui_render_menu_entry_playlist_list (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  materialui_render_scrollbar (TYPE_3__*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 unsigned int menu_display_get_header_height () ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 size_t menu_entries_get_size () ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_2__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_2__*) ; 
 size_t menu_input_get_pointer_selection () ; 
 size_t menu_navigation_get_selection () ; 

__attribute__((used)) static void materialui_render_menu_list(
      materialui_handle_t *mui,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      int x_offset)
{
   size_t i;
   size_t first_entry;
   size_t last_entry;
   file_list_t *list           = NULL;
   size_t entries_end          = menu_entries_get_size();
   unsigned header_height      = menu_display_get_header_height();
   size_t selection            = menu_navigation_get_selection();
   bool touch_feedback_enabled =
         !mui->scrollbar.dragged &&
         (mui->touch_feedback_alpha >= 0.5f) &&
         (mui->touch_feedback_selection == menu_input_get_pointer_selection());

   list = menu_entries_get_selection_buf_ptr(0);
   if (!list)
      return;

   /* Unnecessary sanity check... */
   first_entry = (mui->first_onscreen_entry < entries_end) ? mui->first_onscreen_entry : entries_end;
   last_entry  = (mui->last_onscreen_entry  < entries_end) ? mui->last_onscreen_entry  : entries_end;

   for (i = first_entry; i <= last_entry; i++)
   {
      bool entry_selected        = (selection == i);
      bool touch_feedback_active = touch_feedback_enabled && (mui->touch_feedback_selection == i);
      materialui_node_t *node    = (materialui_node_t*)file_list_get_userdata_at_offset(list, i);
      menu_entry_t entry;

      /* Sanity check */
      if (!node)
         break;

      /* Get current entry */
      menu_entry_init(&entry);
      entry.path_enabled     = false;
      entry.value_enabled    = (mui->list_view_type == MUI_LIST_VIEW_DEFAULT);
      entry.sublabel_enabled = (mui->list_view_type != MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON);
      menu_entry_get(&entry, 0, i, NULL, true);

      /* Render label, value, and associated icons
       * TODO/FIXME: Yes, I know this is ugly...
       * Once we refactor the code to enable alternative
       * non-list-type view modes (e.g. grid, coverflow),
       * this sort of thing will be handled via function
       * pointers (we'll need these in several places:
       * handling pointer input, loading thumbnails,
       * menu drawing, selection highlight drawing,
       * etc.). Until then, a simple switch (and a bunch
       * of duplicated code in the two render_menu_entry
       * functions) will suffice... */
      switch (mui->list_view_type)
      {
         case MUI_LIST_VIEW_PLAYLIST:
         case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_SMALL:
         case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_MEDIUM:
         case MUI_LIST_VIEW_PLAYLIST_THUMB_LIST_LARGE:
            materialui_render_menu_entry_playlist_list(
                  mui,
                  video_info,
                  node,
                  &entry,
                  entry_selected,
                  touch_feedback_active,
                  header_height,
                  width,
                  height,
                  x_offset);
            break;
         case MUI_LIST_VIEW_PLAYLIST_THUMB_DUAL_ICON:
            materialui_render_menu_entry_playlist_dual_icon(
                  mui,
                  video_info,
                  node,
                  &entry,
                  entry_selected,
                  touch_feedback_active,
                  header_height,
                  width,
                  height,
                  x_offset);
            break;
         case MUI_LIST_VIEW_DEFAULT:
         default:
            materialui_render_menu_entry_default(
                  mui,
                  video_info,
                  node,
                  &entry,
                  entry_selected,
                  touch_feedback_active,
                  header_height,
                  width,
                  height,
                  x_offset);
            break;
      }
   }

   /* Draw scrollbar */
   materialui_render_scrollbar(
         mui, video_info, width, height);
}