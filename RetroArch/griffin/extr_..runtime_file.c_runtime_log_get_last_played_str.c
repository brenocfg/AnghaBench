#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  settings_t ;
struct TYPE_5__ {int year; int month; int day; int hour; int minute; int second; } ;
struct TYPE_6__ {TYPE_1__ last_played; } ;
typedef  TYPE_2__ runtime_log_t ;
typedef  enum playlist_sublabel_last_played_style_type { ____Placeholder_playlist_sublabel_last_played_style_type } playlist_sublabel_last_played_style_type ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_INLINE_CORE_DISPLAY_NEVER ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED ; 
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
 int /*<<< orphan*/ * config_get_ptr () ; 
 int /*<<< orphan*/  last_played_strftime (TYPE_2__*,char*,int,char*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int snprintf (char*,size_t,char*,char*,int,int,int,int,...) ; 
 int strlcat (char*,char*,size_t) ; 
 int strlcpy (char*,char*,size_t) ; 

void runtime_log_get_last_played_str(runtime_log_t *runtime_log,
      char *str, size_t len, enum playlist_sublabel_last_played_style_type timedate_style)
{
   settings_t *settings = config_get_ptr();
   int n                = 0;
   char tmp[64];

   tmp[0] = '\0';

   if (!settings)
      return;

   if (runtime_log)
   {
      /* Handle 12-hour clock options
       * > These require extra work, due to AM/PM localisation */
      switch (timedate_style)
      {
         case PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS_AM_PM:
            last_played_strftime(runtime_log, tmp, sizeof(tmp), " %Y/%m/%d - %I:%M:%S %p");
            strlcpy(str, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED), len);
            strlcat(str, tmp, len);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_YMD_HM_AM_PM:
            last_played_strftime(runtime_log, tmp, sizeof(tmp), " %Y/%m/%d - %I:%M %p");
            strlcpy(str, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED), len);
            strlcat(str, tmp, len);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_MDYYYY_AM_PM:
            last_played_strftime(runtime_log, tmp, sizeof(tmp), " %m/%d/%Y - %I:%M %p");
            strlcpy(str, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED), len);
            strlcat(str, tmp, len);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_DM_HM_AM_PM:
            last_played_strftime(runtime_log, tmp, sizeof(tmp), " %d/%m - %I:%M %p");
            strlcpy(str, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED), len);
            strlcat(str, tmp, len);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_MD_HM_AM_PM:
            last_played_strftime(runtime_log, tmp, sizeof(tmp), " %m/%d - %I:%M %p");
            strlcpy(str, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED), len);
            strlcat(str, tmp, len);
            return;
         default:
            break;
      }

      /* Handle non-12-hour clock options */
      switch (timedate_style)
      {
         case PLAYLIST_LAST_PLAYED_STYLE_YMD_HM:
            n = snprintf(str, len, "%s %04u/%02u/%02u - %02u:%02u",
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED),
                  runtime_log->last_played.year, runtime_log->last_played.month, runtime_log->last_played.day,
                  runtime_log->last_played.hour, runtime_log->last_played.minute);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_MDYYYY:
            n = snprintf(str, len, "%s %02u/%02u/%04u - %02u:%02u",
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED),
                  runtime_log->last_played.month, runtime_log->last_played.day, runtime_log->last_played.year,
                  runtime_log->last_played.hour, runtime_log->last_played.minute);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_DM_HM:
            n = snprintf(str, len, "%s %02u/%02u - %02u:%02u",
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED),
                  runtime_log->last_played.day, runtime_log->last_played.month,
                  runtime_log->last_played.hour, runtime_log->last_played.minute);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_MD_HM:
            n = snprintf(str, len, "%s %02u/%02u - %02u:%02u",
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED),
                  runtime_log->last_played.month, runtime_log->last_played.day,
                  runtime_log->last_played.hour, runtime_log->last_played.minute);
            return;
         case PLAYLIST_LAST_PLAYED_STYLE_YMD_HMS:
         default:
            n = snprintf(str, len, "%s %04u/%02u/%02u - %02u:%02u:%02u",
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED),
                  runtime_log->last_played.year, runtime_log->last_played.month, runtime_log->last_played.day,
                  runtime_log->last_played.hour, runtime_log->last_played.minute, runtime_log->last_played.second);
            return;
      }
   }
   else
   {
      n = strlcpy(str, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_SUBLABEL_LAST_PLAYED), len);
      str[n  ]    = ' ';
      str[n+1]    = '\0';
      n = strlcat(str, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_INLINE_CORE_DISPLAY_NEVER), len);
   }

   if ((n < 0) || (n >= 64))
      n = 0; /* Silence GCC warnings... */
}