#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ categories_selection_ptr; int is_playlist; scalar_t__ categories_active_idx_old; void* is_quick_menu; void* is_db_manager_list; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_DATABASE_MANAGER_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_FAVORITES_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_IMAGES_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_PLAYLIST_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_RDB_ENTRY_DETAIL ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_RPL_ENTRY_ACTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_IS_PREVENT_POPULATE ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_UNSET_PREVENT_POPULATE ; 
 unsigned int XMB_SYSTEM_TAB_FAVORITES ; 
 unsigned int XMB_SYSTEM_TAB_HISTORY ; 
 unsigned int XMB_SYSTEM_TAB_IMAGES ; 
 scalar_t__ menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 void* string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 unsigned int xmb_get_system_tab (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  xmb_list_open (TYPE_1__*) ; 
 int /*<<< orphan*/  xmb_list_switch (TYPE_1__*) ; 
 int /*<<< orphan*/  xmb_selection_pointer_changed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmb_set_title (TYPE_1__*) ; 

__attribute__((used)) static void xmb_populate_entries(void *data,
      const char *path,
      const char *label, unsigned k)
{
   xmb_handle_t *xmb = (xmb_handle_t*)data;
   unsigned xmb_system_tab;

   if (!xmb)
      return;

   /* Determine whether this is a playlist */
   xmb_system_tab = xmb_get_system_tab(xmb, (unsigned)xmb->categories_selection_ptr);
   xmb->is_playlist = (xmb_system_tab == XMB_SYSTEM_TAB_FAVORITES) ||
                      (xmb_system_tab == XMB_SYSTEM_TAB_HISTORY) ||
#ifdef HAVE_IMAGEVIEWER
                      (xmb_system_tab == XMB_SYSTEM_TAB_IMAGES) ||
#endif
                      string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_HORIZONTAL_MENU)) ||
                      string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_PLAYLIST_LIST)) ||
                      string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_FAVORITES_LIST)) ||
                      string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_IMAGES_LIST));
   xmb->is_playlist = xmb->is_playlist && !string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_RDB_ENTRY_DETAIL));

   /* Determine whether this is a database manager list */
   xmb->is_db_manager_list = string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_DATABASE_MANAGER_LIST));

   /* Determine whether this is the quick menu */
   xmb->is_quick_menu = string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_RPL_ENTRY_ACTIONS));

   if (menu_driver_ctl(RARCH_MENU_CTL_IS_PREVENT_POPULATE, NULL))
   {
      xmb_selection_pointer_changed(xmb, false);
      menu_driver_ctl(RARCH_MENU_CTL_UNSET_PREVENT_POPULATE, NULL);
      return;
   }

   xmb_set_title(xmb);

   if (xmb->categories_selection_ptr != xmb->categories_active_idx_old)
      xmb_list_switch(xmb);
   else
      xmb_list_open(xmb);
}