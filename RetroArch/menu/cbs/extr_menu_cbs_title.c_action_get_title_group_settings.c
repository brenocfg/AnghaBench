#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int size; TYPE_1__* elems; } ;
typedef  int /*<<< orphan*/  elem1 ;
typedef  int /*<<< orphan*/  elem0 ;
struct TYPE_2__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HISTORY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_IMAGES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MAIN_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MUSIC_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NETPLAY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLISTS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ADD_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HISTORY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_IMAGES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_MAIN_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_MUSIC_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NETPLAY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLISTS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_VIDEO_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_TAB ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char const*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int action_get_title_group_settings(const char *path, const char *label,
      unsigned menu_type, char *s, size_t len)
{
   if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_MAIN_MENU)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_MAIN_MENU), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_HISTORY_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_HISTORY_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_FAVORITES_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_FAVORITES_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_IMAGES_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_IMAGES_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_MUSIC_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_MUSIC_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_VIDEO_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_SETTINGS_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SETTINGS_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLISTS_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_ADD_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ADD_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_NETPLAY_TAB)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_TAB), len);
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_HORIZONTAL_MENU)))
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_HORIZONTAL_MENU), len);
   else
   {
      char elem0[255];
      char elem1[255];
      struct string_list *list_label = string_split(label, "|");

      elem0[0] = elem1[0] = '\0';

      if (list_label)
      {
         if (list_label->size > 0)
         {
            strlcpy(elem0, list_label->elems[0].data, sizeof(elem0));
            if (list_label->size > 1)
               strlcpy(elem1, list_label->elems[1].data, sizeof(elem1));
         }
         string_list_free(list_label);
      }

      strlcpy(s, elem0, len);

      if (!string_is_empty(elem1))
      {
         strlcat(s, " - ", len);
         strlcat(s, elem1, len);
      }
   }

   return 0;
}