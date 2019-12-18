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
typedef  enum playlist_label_display_mode { ____Placeholder_playlist_label_display_mode } playlist_label_display_mode ;

/* Variables and functions */
#define  LABEL_DISPLAY_MODE_KEEP_DISC_INDEX 133 
#define  LABEL_DISPLAY_MODE_KEEP_REGION 132 
#define  LABEL_DISPLAY_MODE_KEEP_REGION_AND_DISC_INDEX 131 
#define  LABEL_DISPLAY_MODE_REMOVE_BRACKETS 130 
#define  LABEL_DISPLAY_MODE_REMOVE_PARENTHESES 129 
#define  LABEL_DISPLAY_MODE_REMOVE_PARENTHESES_AND_BRACKETS 128 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_DEFAULT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_KEEP_DISC_INDEX ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_KEEP_REGION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_KEEP_REGION_AND_DISC_INDEX ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_REMOVE_BRACKETS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_REMOVE_PARENS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_REMOVE_PARENS_AND_BRACKETS ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int playlist_get_label_display_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_playlist_label_display_mode(
      file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   enum playlist_label_display_mode label_display_mode;
   playlist_t *playlist  = playlist_get_cached();

   if (!playlist)
      return;

   label_display_mode = playlist_get_label_display_mode(playlist);

   *w = 19;

   strlcpy(s2, path, len2);

   switch (label_display_mode)
   {
      case LABEL_DISPLAY_MODE_REMOVE_PARENTHESES :
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_REMOVE_PARENS), len);
         break;
      case LABEL_DISPLAY_MODE_REMOVE_BRACKETS :
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_REMOVE_BRACKETS), len);
         break;
      case LABEL_DISPLAY_MODE_REMOVE_PARENTHESES_AND_BRACKETS :
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_REMOVE_PARENS_AND_BRACKETS), len);
         break;
      case LABEL_DISPLAY_MODE_KEEP_DISC_INDEX :
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_KEEP_DISC_INDEX), len);
         break;
      case LABEL_DISPLAY_MODE_KEEP_REGION :
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_KEEP_REGION), len);
         break;
      case LABEL_DISPLAY_MODE_KEEP_REGION_AND_DISC_INDEX :
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_KEEP_REGION_AND_DISC_INDEX), len);
         break;
      default:
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE_DEFAULT), len);
   }
}