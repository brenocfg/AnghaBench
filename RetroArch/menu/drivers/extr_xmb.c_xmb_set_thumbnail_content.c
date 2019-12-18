#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* fullpath; } ;
typedef  TYPE_1__ xmb_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  thumbnail_path_data; scalar_t__ is_db_manager_list; scalar_t__ is_playlist; } ;
typedef  TYPE_2__ xmb_handle_t ;
struct TYPE_8__ {int label_enabled; int rich_label_enabled; int value_enabled; int sublabel_enabled; char const* path; } ;
typedef  TYPE_3__ menu_entry_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_3__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_3__*) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  menu_thumbnail_set_content (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  menu_thumbnail_set_content_image (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  menu_thumbnail_set_content_playlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  playlist_get_cached () ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static void xmb_set_thumbnail_content(void *data, const char *s)
{
   size_t selection  = menu_navigation_get_selection();
   xmb_handle_t *xmb = (xmb_handle_t*)data;
   if (!xmb)
      return;

   if (xmb->is_playlist)
   {
      /* Playlist content */
      if (string_is_empty(s))
         menu_thumbnail_set_content_playlist(xmb->thumbnail_path_data,
               playlist_get_cached(), selection);
   }
   else if (xmb->is_db_manager_list)
   {
      /* Database list content */
      if (string_is_empty(s))
      {
         menu_entry_t entry;

         menu_entry_init(&entry);
         entry.label_enabled      = false;
         entry.rich_label_enabled = false;
         entry.value_enabled      = false;
         entry.sublabel_enabled   = false;
         menu_entry_get(&entry, 0, selection, NULL, true);

         if (!string_is_empty(entry.path))
            menu_thumbnail_set_content(xmb->thumbnail_path_data, entry.path);
      }
   }
   else if (string_is_equal(s, "imageviewer"))
   {
      /* Filebrowser image updates */
      menu_entry_t entry;
      file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
      xmb_node_t *node = (xmb_node_t*)file_list_get_userdata_at_offset(selection_buf, selection);

      menu_entry_init(&entry);
      entry.label_enabled      = false;
      entry.rich_label_enabled = false;
      entry.value_enabled      = false;
      entry.sublabel_enabled   = false;
      menu_entry_get(&entry, 0, selection, NULL, true);

      if (node)
         if (  !string_is_empty(entry.path) && 
               !string_is_empty(node->fullpath))
            menu_thumbnail_set_content_image(xmb->thumbnail_path_data, node->fullpath, entry.path);
   }
   else if (!string_is_empty(s))
   {
      /* Annoying leftovers...
       * This is required to ensure that thumbnails are
       * updated correctly when navigating deeply through
       * the sublevels of database manager lists.
       * Showing thumbnails on database entries is a
       * pointless nuisance and a waste of CPU cycles, IMHO... */
      menu_thumbnail_set_content(xmb->thumbnail_path_data, s);
   }
}