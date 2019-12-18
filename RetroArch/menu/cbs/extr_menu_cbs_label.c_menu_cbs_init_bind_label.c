#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enum_idx; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_LABEL (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  MENU_ENUM_LABEL_CHEAT_BROWSE_MEMORY 135 
#define  MENU_ENUM_LABEL_PLAYLIST_COLLECTION_ENTRY 134 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_SETTINGS 133 
#define  MENU_ENUM_LABEL_RDB_ENTRY_DETAIL 132 
#define  MSG_APPLICATION_DIR 131 
#define  MSG_EXTERNAL_APPLICATION_DIR 130 
#define  MSG_INTERNAL_STORAGE 129 
#define  MSG_REMOVABLE_STORAGE 128 
 int MSG_UNKNOWN ; 
 int /*<<< orphan*/  action_bind_label_application_dir ; 
 int /*<<< orphan*/  action_bind_label_cheat_browse_address ; 
 int /*<<< orphan*/  action_bind_label_external_application_dir ; 
 int /*<<< orphan*/  action_bind_label_generic ; 
 int /*<<< orphan*/  action_bind_label_internal_memory ; 
 int /*<<< orphan*/  action_bind_label_playlist_collection_entry ; 
 int /*<<< orphan*/  action_bind_label_rdb_entry_detail ; 
 int /*<<< orphan*/  action_bind_label_removable_storage ; 

int menu_cbs_init_bind_label(menu_file_list_cbs_t *cbs,
      const char *path, const char *label, unsigned type, size_t idx)
{
   if (!cbs)
      return -1;

   BIND_ACTION_LABEL(cbs, action_bind_label_generic);

   if (cbs->enum_idx != MSG_UNKNOWN)
   {
      switch (cbs->enum_idx)
      {
         case MENU_ENUM_LABEL_PLAYLIST_COLLECTION_ENTRY:
            BIND_ACTION_LABEL(cbs, action_bind_label_playlist_collection_entry);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_SETTINGS:
            BIND_ACTION_LABEL(cbs, action_bind_label_playlist_collection_entry);
            break;
         case MENU_ENUM_LABEL_CHEAT_BROWSE_MEMORY:
            BIND_ACTION_LABEL(cbs, action_bind_label_cheat_browse_address);
            break;
         case MSG_INTERNAL_STORAGE:
            BIND_ACTION_LABEL(cbs, action_bind_label_internal_memory);
            break;
         case MSG_REMOVABLE_STORAGE:
            BIND_ACTION_LABEL(cbs, action_bind_label_removable_storage);
            break;
         case MSG_APPLICATION_DIR:
            BIND_ACTION_LABEL(cbs, action_bind_label_application_dir);
            break;
         case MSG_EXTERNAL_APPLICATION_DIR:
            BIND_ACTION_LABEL(cbs, action_bind_label_external_application_dir);
            break;
         case MENU_ENUM_LABEL_RDB_ENTRY_DETAIL:
            BIND_ACTION_LABEL(cbs, action_bind_label_rdb_entry_detail);
            break;
         default:
            break;
      }
   }

   return -1;
}