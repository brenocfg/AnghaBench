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
typedef  enum playlist_thumbnail_mode { ____Placeholder_playlist_thumbnail_mode } playlist_thumbnail_mode ;
typedef  enum playlist_thumbnail_id { ____Placeholder_playlist_thumbnail_id } playlist_thumbnail_id ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_OFF ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_THUMBNAIL_MODE_DEFAULT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_BOXARTS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_SCREENSHOTS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_TITLE_SCREENS ; 
#define  PLAYLIST_THUMBNAIL_MODE_BOXARTS 131 
#define  PLAYLIST_THUMBNAIL_MODE_OFF 130 
#define  PLAYLIST_THUMBNAIL_MODE_SCREENSHOTS 129 
#define  PLAYLIST_THUMBNAIL_MODE_TITLE_SCREENS 128 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int playlist_get_thumbnail_mode (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *get_playlist_thumbnail_mode_value(playlist_t *playlist, enum playlist_thumbnail_id thumbnail_id)
{
   enum playlist_thumbnail_mode thumbnail_mode =
         playlist_get_thumbnail_mode(playlist, thumbnail_id);

   switch (thumbnail_mode)
   {
      case PLAYLIST_THUMBNAIL_MODE_OFF:
         return msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OFF);
      case PLAYLIST_THUMBNAIL_MODE_SCREENSHOTS:
         return msg_hash_to_str(MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_SCREENSHOTS);
      case PLAYLIST_THUMBNAIL_MODE_TITLE_SCREENS:
         return msg_hash_to_str(MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_TITLE_SCREENS);
      case PLAYLIST_THUMBNAIL_MODE_BOXARTS:
         return msg_hash_to_str(MENU_ENUM_LABEL_VALUE_THUMBNAIL_MODE_BOXARTS);
      default:
         /* PLAYLIST_THUMBNAIL_MODE_DEFAULT */
         break;
   }

   return msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_THUMBNAIL_MODE_DEFAULT);
}