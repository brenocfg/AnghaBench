#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum playlist_thumbnail_mode { ____Placeholder_playlist_thumbnail_mode } playlist_thumbnail_mode ;
typedef  enum playlist_thumbnail_id { ____Placeholder_playlist_thumbnail_id } playlist_thumbnail_id ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
typedef  enum menu_settings_type { ____Placeholder_menu_settings_type } menu_settings_type ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_NO_ITEMS ; 
 int MENU_ENUM_LABEL_VALUE_OFF ; 
 int MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_THUMBNAIL_MODE_DEFAULT ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_BOXARTS ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_SCREENSHOTS ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_TITLE_SCREENS ; 
 int MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_LEFT_THUMBNAIL_MODE ; 
 int MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_RIGHT_THUMBNAIL_MODE ; 
#define  PLAYLIST_THUMBNAIL_MODE_BOXARTS 131 
#define  PLAYLIST_THUMBNAIL_MODE_OFF 130 
#define  PLAYLIST_THUMBNAIL_MODE_SCREENSHOTS 129 
#define  PLAYLIST_THUMBNAIL_MODE_TITLE_SCREENS 128 
 int PLAYLIST_THUMBNAIL_RIGHT ; 
 scalar_t__ menu_entries_append_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_set_checked (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int playlist_get_thumbnail_mode (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned populate_playlist_thumbnail_mode_dropdown_list(
      file_list_t *list, enum playlist_thumbnail_id thumbnail_id)
{
   unsigned count       = 0;
   playlist_t *playlist = playlist_get_cached();

   if (list && playlist)
   {
      size_t i;
      /* Get currently selected thumbnail mode */
      enum playlist_thumbnail_mode current_thumbnail_mode =
            playlist_get_thumbnail_mode(playlist, thumbnail_id);
      /* Get appropriate menu_settings_type (right/left) */
      enum menu_settings_type settings_type =
            (thumbnail_id == PLAYLIST_THUMBNAIL_RIGHT) ?
                  MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_RIGHT_THUMBNAIL_MODE :
                  MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_LEFT_THUMBNAIL_MODE;

      /* Loop over all thumbnail modes */
      for (i = 0; i <= (unsigned)PLAYLIST_THUMBNAIL_MODE_BOXARTS; i++)
      {
         enum msg_hash_enums label_value;
         enum playlist_thumbnail_mode thumbnail_mode =
               (enum playlist_thumbnail_mode)i;

         /* Get appropriate entry label */
         switch (thumbnail_mode)
         {
            case PLAYLIST_THUMBNAIL_MODE_OFF:
               label_value = MENU_ENUM_LABEL_VALUE_OFF;
               break;
            case PLAYLIST_THUMBNAIL_MODE_SCREENSHOTS:
               label_value = MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_SCREENSHOTS;
               break;
            case PLAYLIST_THUMBNAIL_MODE_TITLE_SCREENS:
               label_value = MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_TITLE_SCREENS;
               break;
            case PLAYLIST_THUMBNAIL_MODE_BOXARTS:
               label_value = MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_BOXARTS;
               break;
            default:
               /* PLAYLIST_THUMBNAIL_MODE_DEFAULT */
               label_value = MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_THUMBNAIL_MODE_DEFAULT;
               break;
         }

         /* Add entry */
         if (menu_entries_append_enum(list,
               msg_hash_to_str(label_value),
               "",
               MENU_ENUM_LABEL_NO_ITEMS,
               settings_type,
               0, 0))
            count++;

         /* Add checkmark if item is currently selected */
         if (current_thumbnail_mode == thumbnail_mode)
            menu_entries_set_checked(list, i, true);
      }
   }

   return count;
}