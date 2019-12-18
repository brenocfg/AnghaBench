#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* unsigned_integer; } ;
struct TYPE_6__ {TYPE_1__ target; } ;
struct TYPE_7__ {TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_DM_HM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_DM_HM_AM_PM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MDYYYY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MDYYYY_AM_PM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MD_HM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MD_HM_AM_PM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HMS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HMS_AM_PM ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HM_AM_PM ; 
#define  PLAYLIST_LAST_PLAYED_STYLE_DM_HM 137 
#define  PLAYLIST_LAST_PLAYED_STYLE_DM_HM_AM_PM 136 
#define  PLAYLIST_LAST_PLAYED_STYLE_MDYYYY 135 
#define  PLAYLIST_LAST_PLAYED_STYLE_MDYYYY_AM_PM 134 
#define  PLAYLIST_LAST_PLAYED_STYLE_MD_HM 133 
#define  PLAYLIST_LAST_PLAYED_STYLE_MD_HM_AM_PM 132 
#define  PLAYLIST_LAST_PLAYED_STYLE_YMD_HM 131 
#define  PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS 130 
#define  PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS_AM_PM 129 
#define  PLAYLIST_LAST_PLAYED_STYLE_YMD_HM_AM_PM 128 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void setting_get_string_representation_uint_playlist_sublabel_last_played_style(
      rarch_setting_t *setting,
      char *s, size_t len)
{
   if (!setting)
      return;

   switch (*setting->value.target.unsigned_integer)
   {
      case PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HMS),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_YMD_HM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HM),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_MDYYYY:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MDYYYY),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_DM_HM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_DM_HM),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_MD_HM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MD_HM),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS_AM_PM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HMS_AM_PM),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_YMD_HM_AM_PM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_YMD_HM_AM_PM),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_MDYYYY_AM_PM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MDYYYY_AM_PM),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_DM_HM_AM_PM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_DM_HM_AM_PM),
               len);
         break;
      case PLAYLIST_LAST_PLAYED_STYLE_MD_HM_AM_PM:
         strlcpy(s,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED_STYLE_MD_HM_AM_PM),
               len);
         break;
   }
}